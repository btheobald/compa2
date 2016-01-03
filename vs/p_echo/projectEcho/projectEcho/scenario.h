#pragma once
#include <vector>
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

  // Status Register (8 Bit)
  uint8_t statusReg;
  // G2 G1 G0 WR RD WT ND PS
  /*
  - 0 Paused
  - 1 New Data
  - 2 Waiting
  - 3 Reading
  - 4 Writing
  - 5 General 0
  - 6 General 2
  - 7 General 3
  */

  int newBody(body tempBody);
  int delBody(int index);
  int delAllBodies(int index);
  // Get Body Pointer - For GUI?
};

