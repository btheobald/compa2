#pragma once

#include "scenario.hpp"
#include <vector>

class render: public scenario {
private:
  void drawBody(body* p_b);

public:
  void createSuperstructure(int p_soBodies, double p_cMass, double p_oMass, double p_cRadius, double p_oRadius, double p_cPosX, double p_cPosY, double p_cVelX, double p_cVelY, double p_coSpacing, double p_sRadius);
  void drawScene(void);
  int checkCoord(double x, double y, double ad);

  // Return a pointer of storage for interface
  inline control* returnControlPointer() { return &lControl; }
  inline std::vector<body*>* returnBodiesPointer() { return &bodies; }

  // Provides public interface to base class private variables
  control& pControl = lControl;
  std::vector<body*>& pBodies = bodies;
};
