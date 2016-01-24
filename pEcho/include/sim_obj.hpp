#pragma once
#include "scenario.hpp"
#define ITTERATIONS 1000000

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

  #ifdef OUTPUT
  double outputData[ITTERATIONS][3][2];
  #endif

public:
  sim_obj();
  ~sim_obj();
  int itteration();
  #ifdef OUTPUT
  void outputStore(int itteration);
  void outputToTerm();
  #endif
};
