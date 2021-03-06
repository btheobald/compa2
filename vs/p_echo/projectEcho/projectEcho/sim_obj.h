#pragma once
#include "scenario.h"

class sim_obj : public scenario {
private:
  int prevBodyCount = 0;
  vector<vector<double>> forceMatrix;
  void resizeMatrix(vector<vector<double>> &p_Matrix, int newSize);
  double calcCompDistance(int bodyID_A, int bodyID_B, int xy);
  double calcVectDistance(double distX, double distY);
  double calcForceBodyPair(int bodyID_A, int bodyID_B, int xy);
  int calcForceMatrix();
  int calcForceSumAB();
  int calcAcceleraitonAB();
  int calcHalfVelocityAB();
  int calcPositionAB();

public:
  sim_obj();
  ~sim_obj();
  int itteration();
  void outputTest(int itteration);
};

