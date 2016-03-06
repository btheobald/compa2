#pragma once

#include "scenario.hpp"

class simulation: public scenario {
private:
  // Distance calculations.
  double getComponentDistance(body* bA, body* bB, int xy);
  double getVectorDistance(double dX, double dY);

  /* Forces are calulated and directly put into bodies as acceleration
    - Acceleration is summed up for each relationship that a body has
    - In order to reduce the ammount of calculation, the algorthim can be likened to graph theory, however in order to keep withn the constrains of memory, there is no storage matrix used as this would result in n^2 memory usage.
    - Pattern:
    + 0 1 2 3 4 5
    0 -
    1 x -
    2 x x -
    3 x x x -
    4 x x x x -
    5 x x x x x -
    - Each calculation done is applied to both bodies for x and y.
    - The other body has the sign of the forces flipped.
  */
  void resetAllAcceleration(void);
  void calcAcceleration(body* bA, body* bB);
  void calcAllAcceleration();

  void calcAllCollisions(void);
  void calcAllHalfVelocity(void);
  void calcAllPosition(void);

public:
  void itteration(void);

};
