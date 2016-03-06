#pragma once

#include "scenario.hpp"

class simulation: public scenario {
private:
  double getComponentDistance(body* bA, body* bB, int xy);
  double getVectorDistance(body* bA, body* bB);

  void resetAcceleration(void);
  double calcAcceleration(body* bA, body* bB);
  double calcAllAcceleration();
  double calcAllCollisions();
  double calcAllHalfVelocity();
  double calcAllPosition();

public:
  void itteration();

};
