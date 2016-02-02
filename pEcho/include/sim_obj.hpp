#pragma once
// Standard Library Includes
#include <thread>
// Custom Includes
#include "scenario.hpp"
#include "com.hpp"

class sim_obj : public scenario {
private:
  int prevBodyCount = 0;
  com::double2DVector forceMatrix;
  double calcCompDistance(int bodyID_A, int bodyID_B, int xy);
  double calcVectDistance(double distX, double distY);
  double calcForceBodyPair(int bodyID_A, int bodyID_B, double distV);
  int calcForceMatrix(int range_L, int range_H);
  int calcForceSumAB(int range_L, int range_H);
  int calcAcceleraitonAB(int range_L, int range_H);
  int calcHalfVelocityAB(int range_L, int range_H);
  int calcPositionAB(int range_L, int range_H);

public:
  sim_obj();
  ~sim_obj();
  void resizeMatrix(com::double2DVector &p_Matrix, int newSize);
  int getThreadCount(void);
  int getRange(int usingThreads, int threadID, bool lowerHigher);
  int itteration_vp(int range_L, int range_H);
  int itteration_f(int range_L, int range_H);
  int itteration_av(int range_L, int range_H);
  void preItteration();
};
