#pragma once
// Custom Includes
#include "scenario.hpp"
#include "com.hpp"

class sim_obj : public scenario {
private:
  int prevBodyCount = 0;
  com::double2DVector forceMatrix;
  void resizeMatrix(com::double2DVector &p_Matrix, int newSize);
  double calcCompDistance(int bodyID_A, int bodyID_B, int xy);
  double calcVectDistance(double distX, double distY);
  double calcForceBodyPair(int bodyID_A, int bodyID_B, double distV);
  int calcForceMatrix();
  int calcForceSumAB();
  int calcAcceleraitonAB();
  int calcHalfVelocityAB();
  int calcPositionAB();

public:
  sim_obj();
  ~sim_obj();
  int itteration();
};
