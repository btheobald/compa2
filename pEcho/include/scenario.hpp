#pragma once
#include <vector>
#include <cstdint>
#include "body.hpp"
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

  void newBody(body *tempptr);
  void delBody(int index);
  void delAllBodies(int index);
  void populateBodyStore(vector<body> tempStore);
  vector<body> returnBodyStore();

  void setUGC(double p_GravConst);
  void setIDT(double p_Timestep);
  void setIPF(double p_Timestep);
};
