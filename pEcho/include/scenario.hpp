#pragma once
// Custom Includes
#include "body.hpp"
#include "com.hpp"

class scenario {
protected:
  // Body Storage
  com::bodyVector bodyStore; // List, C++ Std library vector, dynamic array.

  // Simulation Physical Constants (Can be modified)
  double UGC;
  double IDT;
  int IPF;

  bool scenarioChanged = true;

public:
  scenario();
  ~scenario();

  void newBody(double p_Mass, double p_Radius, double p_PosX, double p_PosY, double p_VelX, double p_VelY);
  void newBody(double p_PosX, double p_PosY);
  void delBody(int index);
  void delAllBodies(int index);
  void populateBodyStore(com::bodyVector tempStore);
  com::bodyVector returnBodyStore();

  void setUGC(double p_UGC);
  void setIDT(double p_IDT);
  void setIPF(int p_IPF);

  double getUGC();
  double getIDT();
  int getIPF();
};
