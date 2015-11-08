#include <iostream>
#include <cmath>
#include <unistd.h>

#define GRAVCONST 1
#define TIMESTEP 0.01

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
  int i = 0, xy;
  double currentAngle;
  double forceCalc, distance, diffX, diffY;
  double forceX, forceY;
  double deltaVelX, deltaVelY;
  double deltaPosX, deltaPosY;
  
  double deltaVelXs, deltaVelYs;
  double deltaPosXs, deltaPosYs;
  
  // Setup
  // M0
  currentBodies[0].mass = 100;
  currentBodies[0].position[0] = 0.0;
  currentBodies[0].position[1] = 0.0;
  // M1
  currentBodies[1].mass = 1;
  currentBodies[1].position[0] = 0.0;
  currentBodies[1].position[1] = 100;
  currentBodies[1].velocity[0] = 3.5;
  currentBodies[1].velocity[1] = 0.0;
  
  //cout << "1x, 1y" << endl;
  
  // Simulation
  while (i < 10) {
    // Calculate Distance bettween Bodies
    diffX = currentBodies[0].position[0] - currentBodies[1].position[0];
    diffY = currentBodies[0].position[1] - currentBodies[1].position[1];
    distance = sqrt(pow(diffX,2) + pow(diffY,2));    

    // Calculate Gravitational Force
    forceCalc = -((GRAVCONST * currentBodies[0].mass * currentBodies[1].mass) / (pow(distance,2)));
    
    // Find Angle Relative to X and resolve forces.
    currentAngle = atan(diffY/diffX);
    forceX = forceCalc * cos(currentAngle);
    forceY = forceCalc * sin(currentAngle);
    if(diffX > 0) {
	forceX = -forceX;
	forceY = -forceY;
    }
    
    // Put forces into body data
    currentBodies[1].force[0] = forceX;
    currentBodies[1].force[1] = forceY;
    
    // Put forces into body data SB
    currentBodies[0].force[0] = forceX;
    currentBodies[0].force[1] = forceY;
    
    // Calculate Acceleration
    currentBodies[1].acceleration[0] = currentBodies[1].force[0] / currentBodies[1].mass;
    currentBodies[1].acceleration[1] = currentBodies[1].force[1] / currentBodies[1].mass;
    
    // Calculate Acceleration SB
    currentBodies[0].acceleration[0] = currentBodies[0].force[0] / currentBodies[0].mass;
    currentBodies[0].acceleration[1] = currentBodies[0].force[1] / currentBodies[0].mass;
    
    // Calculate delta velocity
    deltaVelX = currentBodies[1].acceleration[0] / TIMESTEP;
    deltaVelY = currentBodies[1].acceleration[1] / TIMESTEP;
    
    // Calculate delta velocity SB
    deltaVelXs = currentBodies[0].acceleration[0] / TIMESTEP;
    deltaVelYs = currentBodies[0].acceleration[1] / TIMESTEP;
    
    // Calculate position delta (S = ut + 0.5 * at^2)
    deltaPosX = (currentBodies[1].velocity[0] * TIMESTEP + (0.5 * (currentBodies[1].acceleration[0] * pow(TIMESTEP,2))));
    deltaPosY = (currentBodies[1].velocity[1] * TIMESTEP + (0.5 * (currentBodies[1].acceleration[1] * pow(TIMESTEP,2))));
    
    // Calculate position delta (S = ut + 0.5 * at^2) SB
    deltaPosXs = (currentBodies[0].velocity[0] * TIMESTEP + (0.5 * (currentBodies[0].acceleration[0] * pow(TIMESTEP,2))));
    deltaPosYs = (currentBodies[0].velocity[1] * TIMESTEP + (0.5 * (currentBodies[0].acceleration[1] * pow(TIMESTEP,2))));
    
    // Update Velocity
    currentBodies[1].velocity[0] += deltaVelX;
    currentBodies[1].velocity[1] += deltaVelY;
    
    // Update Velocity SB
    currentBodies[0].velocity[0] += deltaVelXs;
    currentBodies[0].velocity[1] += deltaVelYs;

    // Update Position
    currentBodies[1].position[0] += deltaPosX;
    currentBodies[1].position[1] += deltaPosY;
    
    // Update Position SB
    //currentBodies[0].position[0] += deltaPosXs;
    //currentBodies[0].position[1] += deltaPosYs;
    
    cout << currentBodies[1].position[0] << ", " << currentBodies[1].position[1] << endl;
    i++;
  }
}















