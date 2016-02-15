#pragma once
// Standard Library Includes
#include <iostream>
#include <cmath>
// Custom Includes
#include "scenario.hpp"
#include "sharedStage.hpp"
#include "com.hpp"

class sim_obj : public scenario {
private:
  int prevBodyCount = 0;
  com::float2DVector forceMatrix;
  void resizeMatrix(com::float2DVector &p_Matrix, int newSize);
  float calcCompDistance(int bodyID_A, int bodyID_B, int xy);
  float calcVectDistance(float distX, float distY);
  float calcForceBodyPair(int bodyID_A, int bodyID_B, float distV);
  int calcForceMatrix();
  int calcForceSumAB();
  int calcAcceleraitonAB();
  int calcHalfVelocityAB();
  int calcPositionAB();
  void calcCollision();

public:
  sim_obj();
  ~sim_obj();
  int itteration();
  void updateSharedArea(sharedStage* l_sharedDataAccess);
  void updateLocalStore(sharedStage* l_sharedDataAccess);
};
