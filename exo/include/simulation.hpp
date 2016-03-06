#pragma once

#include "scenario.hpp"

class simulation: public scenario {
private:
  double getComponentDistance(body* bA, body* bB, int xy);
  double getVectorDistance(double dX, double dY);

  void resetAcceleration(void);
  void calcAcceleration(body* bA, body* bB);
  void calcAllAcceleration();
  void calcAllCollisions();
  void calcAllHalfVelocity();
  void calcAllPosition();

public:
  void itteration();

};
