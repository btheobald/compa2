#pragma once
#include "scenario.h"

class sim_obj : public scenario {
private:
  vector<vector<double>> forceMatrix;
  double calcForceBodyPair(int bodyID_A, int bodyID_B);
  int calculateForces();
public:
  sim_obj();
  ~sim_obj();
};

