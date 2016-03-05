#pragma once
// Standard Library Includes
#include <vector>

// Custom Includes
#include "body.hpp"
#include "sharedStage.hpp"
#include "com.hpp"

class scenario {
protected:
  // Body Storage
  com::bodyVector bodyStore; // List, C++ Std library vector, dynamic array.

  // Simulation Physical Constants (Can be modified)
  double UGC;
  double IDT;
  int IPF;
  bool collisions;

  bool scenarioChanged = true;
  void populateBodyStore(com::bodyVector tempStore);
  com::bodyVector returnBodyStore();

public:
  scenario();
  ~scenario();

  void newBody(double p_Mass, double p_Radius, double p_PosX, double p_PosY, double p_VelX, double p_VelY, const float p_Color[3]);
  void delBody(int index);
  void delAllBodies(int index);

  void updateLocalControl(sharedStage* l_sharedDataAccess);
  void updateLocalControl(double p_UGC, double p_IDT, int p_IPF, bool collisions);

  void updateSharedControl(sharedStage* l_sharedDataAccess);

  double getUGC();
  double getIDT();
  int getIPF();
};
