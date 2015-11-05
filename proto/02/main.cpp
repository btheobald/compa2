#include <iostream>
#include <cmath>
#include <unistd.h>

#define GRAVCONST 6.67E-11
#define TIMESTEP 1

using namespace std;

// Types 
typedef struct {
  // Properties
  double mass = 0.0;
  // State
  double force[2] = {0.0, 0.0};
  double acceleration[2] = {0.0, 0.0};
  double velocity[2] = {0.0, 0.0};
  double position[2] = {0.0, 0.0};
} sBody; // Single Body;

typedef sBody bodyPair[2];
typedef sBody scenario[8];

// Prototypes

// Functions
int main() {
  bodyPair currentBodies;
  int i, xy;
  double currentForce, currentAngle;
  
  // M0
  currentBodies[0].mass = 100;
  currentBodies[0].position[0] = 0.0;
  currentBodies[0].position[1] = 0.0;
  // M1
  currentBodies[1].mass = 1;
  currentBodies[1].position[0] = 0.0;
  currentBodies[1].position[1] = 40;
  currentBodies[1].velocity[0] = 2.5;
  currentBodies[1].velocity[1] = 0.0;
  
  while (1) {

  }
