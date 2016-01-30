#include "sim_obj.hpp"
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

void sim_obj::resizeMatrix(vector<vector<double>>& p_Matrix, int newSize) {
  p_Matrix.clear();
  p_Matrix.resize(newSize, vector<double>(newSize, 0));
}

double sim_obj::calcCompDistance(int bodyID_A, int bodyID_B, int xy) {
  double posA = bodyStore[bodyID_A].getPosition(xy);
  double posB = bodyStore[bodyID_B].getPosition(xy);
  // Return component distance
  return posA - posB;
}

double sim_obj::calcVectDistance(double distX, double distY) {
  return sqrt(pow(abs(distX),2) + pow(abs(distY), 2));
}

double sim_obj::calcForceBodyPair(int bodyID_A, int bodyID_B, int xy) {
  double distX, distY, distV;
  // Component Distance
  distX = calcCompDistance(bodyID_A, bodyID_B, 0);
  distY = calcCompDistance(bodyID_A, bodyID_B, 1);
  // Vector Distance
  distV = calcVectDistance(distX, distY);

  // GMm/(r^3)
  double forceResult;
  forceResult = UGC * bodyStore[bodyID_A].getMass() * bodyStore[bodyID_B].getMass();
  forceResult /= pow(distV, 3);

  if (xy)
    forceResult *= distY;
  else
    forceResult *= distX;
  return -forceResult;
}


int sim_obj::calcForceMatrix() {
  resizeMatrix(forceMatrix, bodyStore.size());
  prevBodyCount = bodyStore.size();

  // Loop Half Matrix
  for (unsigned int xAccess = 0; xAccess < bodyStore.size(); xAccess++) {
    for (unsigned int yAccess = xAccess + 1; yAccess < bodyStore.size(); yAccess++) {
      // Skip if checking same body
      if (xAccess != yAccess) {
        forceMatrix[xAccess][yAccess] = calcForceBodyPair(xAccess, yAccess, 0);
        forceMatrix[yAccess][xAccess] = calcForceBodyPair(xAccess, yAccess, 1);
      }
    }
  }

  // Return Success
  return 0;
}
// Applies to All Bodies, sets in body vector.
int sim_obj::calcForceSumAB() {
  for (unsigned int bodyIDC = 0; bodyIDC < bodyStore.size(); bodyIDC++) {
    bodyStore[bodyIDC].resetForce();
  }
  for (unsigned int xAccess = 0; xAccess < bodyStore.size(); xAccess++) {
    for (unsigned int yAccess = 0; yAccess < bodyStore.size(); yAccess++) {
      // Ignore Middle Diagonal
      if (yAccess != xAccess) {
        // If yAccess is smaller than xAccess, flip coordinates to stay within half matrix.
        if (yAccess < xAccess) {
          // Add Component force to get total component forces for x and y.
          bodyStore[xAccess].addForce(-forceMatrix[yAccess][xAccess], 0);
          bodyStore[yAccess].addForce( forceMatrix[xAccess][yAccess], 1);
        } else {
          bodyStore[xAccess].addForce( forceMatrix[xAccess][yAccess], 0);
          bodyStore[yAccess].addForce(-forceMatrix[yAccess][xAccess], 1);
        }
      }
    }
  }
  return 0;
}

int sim_obj::calcAcceleraitonAB() {
  // Update Forces before Acceleration Update
  for (unsigned int bodyIDC = 0; bodyIDC < bodyStore.size(); bodyIDC++) {
    bodyStore[bodyIDC].calcAcceleration();
    //cout << bodyIDC << " : " << bodyStore[bodyIDC].getAcceleration(0) << ", " << bodyStore[bodyIDC].getAcceleration(1) << endl;
  }
  return 0;
}

int sim_obj::calcHalfVelocityAB() {
  for (unsigned int bodyIDC = 0; bodyIDC < bodyStore.size(); bodyIDC++) {
    bodyStore[bodyIDC].calcHalfVelocity(IDT);
    //cout << bodyIDC << " : " << bodyStore[bodyIDC].getVelocity(0) << ", " << bodyStore[bodyIDC].getVelocity(1) << endl;
  }
  return 0;
}

int sim_obj::calcPositionAB() {
  for (unsigned int bodyIDC = 0; bodyIDC < bodyStore.size(); bodyIDC++) {
    bodyStore[bodyIDC].calcPosition(IDT);
  }
  return 0;
}

sim_obj::sim_obj() {
}

sim_obj::~sim_obj() {
}

int sim_obj::itteration() {
  if (scenarioChanged) {
    // Calculate Initial Forces and Accelerations
    calcForceMatrix();
    calcForceSumAB();
    calcAcceleraitonAB();
    scenarioChanged = false;
  }

  // Move Half for Half Time
  calcHalfVelocityAB();
  calcPositionAB();

  // Update Forces and Accelerations
  calcForceMatrix();
  calcForceSumAB();
  calcAcceleraitonAB();

  // Calculate New Velocity
  calcHalfVelocityAB();

  //cout << bodyStore[1].getPosition(0) << " " << bodyStore[1].getPosition(1) << endl;

  return 0;
}
