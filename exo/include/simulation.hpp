#pragma once
// Base class include
#include "scenario.hpp"

class simulation: public scenario {
private:
  // Distance calculations.
  double getComponentDistance(body* bA, body* bB, int xy);
  double getVectorDistance(double dX, double dY);

  /* Forces are calulated and directly put into bodies as acceleration
    - Acceleration is summed up for each relationship that a body has.
    - In order to reduce the ammount of calculation, the algorthim can be visualised best using graph theory. In order to keep memory usage to a minimum, there is no storage matrix used as this would result in n^2 memory usage.
    - Pattern:
    + 0 1 2 3 4
    0 -
    1 x -
    2 x x -
    3 x x x -
    4 x x x x -
    - Each calculation done is applied to both bodies for x and y.
    - The other body has the sign of the forces flipped. (The relationship is flipped.)
  */
  void resetAllAcceleration(void);
  void calcAcceleration(body* bA, body* bB);
  void calcAllAcceleration(void);

  void calcAllCollisions(void);
  void lawsOfPhysicsCheck(void);

  // Calls functions in individual bodies
  void calcAllHalfVelocity(void);
  void calcAllPosition(void);

public:
  void initialCalc(void);
  void itteration(void);

  virtual inline int getIPF(void) { return lControl.IPF; };
};
