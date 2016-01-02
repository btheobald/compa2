#pragma once
#include <list>
#include "body.h"
using namespace std;

class scenario {
private:
  // Body Storage
  list<body> bodyStore; // List, C++ Std library double linked list, initally empty. (body class type)
  
  // Simulation Physical Constants (Can be modified by main thread)
  double timestep;
  int itterationsPerFrame;
  double gravitationalConstant;

  // Status Register
  char statusReg;  
  /*
  Bit Mapping
  - 0 Paused
  - 1 New Data
  - 2 Waiting
  - 3 Reading
  - 4 Writing
  - 5 General 0
  - 6 General 2
  - 7 General 3
  */

public:
  scenario();
  ~scenario();

  addBody();
};

