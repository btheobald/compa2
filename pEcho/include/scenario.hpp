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
  float UGC;
  float IDT;
  int IPF;

  bool scenarioChanged = true;
  void populateBodyStore(com::bodyVector tempStore);
  com::bodyVector returnBodyStore();

public:
  scenario();
  ~scenario();

  void newBody(float p_Mass, float p_Radius, float p_PosX, float p_PosY, float p_VelX, float p_VelY, const float p_Color[3]);
  void delBody(int index);
  void delAllBodies(int index);

  void updateLocalControl(sharedStage* l_sharedDataAccess);
  void updateLocalControl(float p_UGC, float p_IDT, int p_IPF);

  void updateSharedControl(sharedStage* l_sharedDataAccess);

  float getUGC();
  float getIDT();
  int getIPF();
};
