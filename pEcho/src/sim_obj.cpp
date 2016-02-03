// Header Include
#include "sim_obj.hpp"

void sim_obj::resizeMatrix(com::double2DVector &p_Matrix, int newSize) {
  p_Matrix.clear();
  p_Matrix.resize(newSize, std::vector<double>(newSize, 0));
  prevBodyCount = bodyStore.size();
}

double sim_obj::calcCompDistance(int bodyID_A, int bodyID_B, int xy) {
  double posA = bodyStore[bodyID_A].getPosition(xy);
  double posB = bodyStore[bodyID_B].getPosition(xy);
  // Return component distance
  return posA - posB;
}

double sim_obj::calcVectDistance(double distX, double distY) {
  return sqrt(pow(fabs(distX),2) + pow(fabs(distY), 2));
}

double sim_obj::calcForceBodyPair(int bodyID_A, int bodyID_B, double distV) {
  // GMm/(r^3)
  double forceResult;
  forceResult = UGC * bodyStore[bodyID_A].getMass() * bodyStore[bodyID_B].getMass();
  forceResult = forceResult / pow(distV, 3);

  return forceResult;
}

int sim_obj::calcForceMatrix(int range_L, int range_H) {
  double tempPreForce, distX, distY, distV;

  // Loop Half Matrix
  for (int xAccess = 0; xAccess < bodyStore.size(); xAccess++) {
    for (unsigned int yAccess = xAccess + 1; yAccess < bodyStore.size(); yAccess++) {
      // Skip if checking same body
      if (xAccess != yAccess) {
        if (((xAccess >= range_L) & (xAccess <= range_H)) | ((yAccess >= range_L) & (yAccess <= range_H))) {
          // Calculate Distances
          distX = calcCompDistance(xAccess, yAccess, 0);
          distY = calcCompDistance(xAccess, yAccess, 1);
          distV = calcVectDistance(distX, distY);

          tempPreForce = calcForceBodyPair(xAccess, yAccess, distV);
          forceMatrix[xAccess][yAccess] = -tempPreForce * distX;
          forceMatrix[yAccess][xAccess] = -tempPreForce * distY;
        }
      }
    }
  }

  // Return Success
  return 0;
}

void sim_obj::clearForces() {
  for (int bodyIDC = 0; bodyIDC < bodyStore.size(); bodyIDC++) {
    bodyStore[bodyIDC].resetForce();
  }
}

// Applies to All Bodies, sets in body vector.
int sim_obj::calcForceSumAB(int range_L, int range_H) {
  for (int xAccess = range_L; xAccess < range_H; xAccess++) {
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

int sim_obj::calcAcceleraitonAB(int range_L, int range_H) {
  // Update Forces before Acceleration Update
  for (int bodyIDC = range_L; bodyIDC < range_H; bodyIDC++) {
    bodyStore[bodyIDC].calcAcceleration();
    //cout << bodyIDC << " : " << bodyStore[bodyIDC].getAcceleration(0) << ", " << bodyStore[bodyIDC].getAcceleration(1) << endl;
  }
  return 0;
}

int sim_obj::calcHalfVelocityAB(int range_L, int range_H) {
  for (int bodyIDC = range_L; bodyIDC < range_H; bodyIDC++) {
    bodyStore[bodyIDC].calcHalfVelocity(IDT);
    //cout << bodyIDC << " : " << bodyStore[bodyIDC].getVelocity(0) << ", " << bodyStore[bodyIDC].getVelocity(1) << endl;
  }
  return 0;
}

int sim_obj::calcPositionAB(int range_L, int range_H) {
  for (int bodyIDC = range_L; bodyIDC < range_H; bodyIDC++) {
    bodyStore[bodyIDC].calcPosition(IDT);
  }
  return 0;
}

sim_obj::sim_obj() {
}

sim_obj::~sim_obj() {
}

int sim_obj::itteration_vp(int range_L, int range_H) {
  calcHalfVelocityAB(range_L, range_H);
  calcPositionAB(range_L, range_H);
  return 0;
}

int sim_obj::itteration_f(int range_L, int range_H) {
  calcForceMatrix(range_L, range_H);
  calcForceSumAB(range_L, range_H);
  return 0;
}

int sim_obj::itteration_av(int range_L, int range_H) {
  calcAcceleraitonAB(range_L, range_H);
  calcHalfVelocityAB(range_L, range_H);
  return 0;
}

int sim_obj::getThreadCount(void) {
  unsigned int avaliableThreads = std::thread::hardware_concurrency();
  unsigned int bodyCount = bodyStore.size();

  if(bodyCount < avaliableThreads) {
    return 1;
  } else {
    return avaliableThreads;
  }
}

int sim_obj::getRange(int usingThreads, int threadID, bool lowerHigher) {
  unsigned int bodyCount = bodyStore.size();
  unsigned int excess = bodyCount % usingThreads;
  unsigned int toSplit = (bodyCount - excess) / usingThreads;

  if(usingThreads == 1) {
    if(lowerHigher) {
      // Higher Range
      return bodyCount;
    } else {
      // Lower Range
      return 0;
    }
  }

  if(lowerHigher) {
    // Higher Range
    return toSplit * (threadID+1) + excess;;
  } else {
    // Lower Range
    if(threadID != 0)
      return toSplit * (threadID) + excess;
    else
      return toSplit * (threadID);
  }
}

void sim_obj::preItteration() {
  resizeMatrix(forceMatrix, bodyStore.size());
  clearForces();
}
