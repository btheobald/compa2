#pragma once
#include <vector>
#include <cstdint>
#include "body.h"
using namespace std;

class scenario {
protected:
  // Body Storage
  vector<body> bodyStore; // List, C++ Std library vector, dynamic array.

  // Simulation Physical Constants (Can be modified)
  double timestep;
  int itterationsPerFrame;
  double gravitationalConstant;

  bool scenarioChanged = true;

public:
  scenario();
  ~scenario();

  int newBody(body *tempptr);
  int delBody(int index);
  int delAllBodies(int index);
  // Get Body Pointer - For GUI?

  int setTimestep(double p_Timestep);
  int setGravConst(double p_GravConst);
};
