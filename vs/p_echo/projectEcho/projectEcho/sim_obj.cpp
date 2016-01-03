#include "sim_obj.h"
#include <vector>
#include <cmath>

void sim_obj::resizeMatrix(vector<vector<double>>& p_Matrix, int newSize) {
  p_Matrix.clear();
  p_Matrix.resize(newSize, vector<double>(newSize, 0));
}

double sim_obj::calcCompDistance(int bodyID_A, int bodyID_B, int xy) {
  double posA = bodyStore.at(bodyID_A).getPosition(xy);
  double posB = bodyStore.at(bodyID_B).getPosition(xy);
  // Return absolute distance
  return abs(posA - posB);
}

double sim_obj::calcVectDistance(double distX, double distY) {
  return sqrt(pow(distX,2) + pow(distY, 2));
}

// TODO: REVIEW THIS CODE
double* sim_obj::calcForceBodyPair(int bodyID_A, int bodyID_B) {
  double distX, distY, distV;
  // Component Distance
  distX = calcCompDistance(bodyID_A, bodyID_B, 0);
  distY = calcCompDistance(bodyID_B, bodyID_B, 1);
  // Vector Distance
  distV = calcVectDistance(distX, distY);
  
  // GMm/(r^3)
  double forceResult, forceReturn[2];
  forceResult = gravitationalConstant * bodyStore.at(bodyID_A).getMass() * bodyStore.at(bodyID_B).getMass();
  forceResult /= pow(distV, 3);
  
  forceReturn[0] = forceResult * distX;
  forceReturn[1] = forceResult * distY;
  return forceReturn; // REVIEW THIS CODE
}

int sim_obj::calculateForceMatrix() {
  // Check if Body Count has Changed
  int cBodyCount = bodyStore.size();
  if (cBodyCount != prevBodyCount) {
    resizeMatrix(forceMatrix, cBodyCount);
  }
  
  // Loop Half Matrix
  for (int xAccess = 0; xAccess < cBodyCount; xAccess) {
    for (int yAccess = 0; xAccess < cBodyCount; yAccess) {
      double *xyForce = calcForceBodyPair(xAccess, yAccess);
      forceMatrix.at(xAccess).at(yAccess) = xyForce[0];
      forceMatrix.at(yAccess).at(xAccess) = xyForce[1];
    }
  }

  // Return Success
  return 0;
}

sim_obj::sim_obj() {
}

sim_obj::~sim_obj() {
}
