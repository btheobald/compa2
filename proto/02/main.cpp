#include <iostream>
#include <cmath>
#include <unistd.h>

#define GRAVCONST 1
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

// Prototypes

// Functions
int main() {
  bodyPair currentBodies;
  int i, xy;
  double currentAngle;
  double force_calc, distance, xdiff, ydiff;
  double xforce, yforce;
  
  // Setup
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
  
  // Simulation
  //while (1) {
    // Calculate Distance bettween Bodies
    xdiff = currentBodies[0].position[0] - currentBodies[1].position[0];
    ydiff = currentBodies[0].position[1] - currentBodies[1].position[1];
    distance = sqrt(pow(xdiff,2)+pow(ydiff,2));
    
    // Calculate Gravitational Force
    force_calc = -((GRAVCONST * currentBodies[0].mass * currentBodies[1].mass) / pow(distance,2));
    
    // Find Angle Relative to X and resolve forces.
    if (xdiff == 0) {
      yforce = force_calc;
      xforce = 0;
    } else 
    if (ydiff == 0) {
      xforce = force_calc;
      yforce = 0;
    } else {
      currentAngle = atan(ydiff/xdiff);
      xforce = force_calc * cos(currentAngle);
      yforce = force_calc * sin(currentAngle);
    }
    
    // Put forces into body data.
    currentBodies[1].force[0] = xforce;
    currentBodies[1].force[1] = yforce;
    
    // Calculate Acceleration
    currentBodies[1].acceleration[0] = currentBodies[1].force[0] / currentBodies[1].mass;
    currentBodies[1].acceleration[1] = currentBodies[1].force[1] / currentBodies[1].mass;
    
    // Calculate change in Velocity and add to body data velocity
    currentBodies[1].velocity[0] += currentBodies[1].acceleration[0] / TIMESTEP;
    currentBodies[1].velocity[1] += currentBodies[1].acceleration[1] / TIMESTEP;

    cout << xforce << endl;
    cout << yforce << endl;
    cout << currentBodies[1].velocity[0] << endl;
    cout << currentBodies[1].velocity[1] << endl;
  //}
}















