#include <iostream>
#include <cmath>

using namespace std;

int main() {
  // Body Data
  double position_r[2], velocity[2], acceleration[2];
  // Time Variables
  double deltaT, simTime;
  const double outputTime = 0.01;
  double tc = outputTime;
  
  // Setup Initial Parameters
  cerr << "Enter Timestep (s): ";
  cin >> deltaT;
  cerr << "Enter Simulation Time (s): ";
  cin >> simTime;
  
  // Relative Position XY
  position_r[0] = 1.0;
  position_r[1] = 0.0;
  // Velocity XY
  velocity[0] = 0.0;
  velocity[1] = 0.5;
  
  // Calculate Initial System Total Energy
  double e_k = 0.5 * (pow(velocity[0],2) + pow(velocity[1],2)); // Kinetic Energy
  double e_p = - 1.0 / sqrt(pow(position_r[0],2) + pow(position_r[1],2)); // Potential Energy
  double e_i = e_k + e_p; // Initial Energy
  
  // Calculate Initial Acceleration
  double r2 = pow(position_r[0],2) + pow(position_r[1],2);
  for (int c = 0; c < 2; c++) {
    acceleration[c] = - position_r[c] / (r2 * sqrt(r2));
  }
  
  // Simulations
  for (double t = 0; t < simTime; t += deltaT) {
    // Calculate New Velocity and Position
    for (int c = 0; c < 2; c++) {
      velocity[c] += 0.5 * acceleration[c] * deltaT;
      position_r[c] += velocity[c] * deltaT;
    }
    
    // Calculate New Acceleration and Velocity
    r2 = pow(position_r[0],2) + pow(position_r[1],2);
    for (int c = 0; c < 2; c++) {
      acceleration[c] = - position_r[c] / (r2 * sqrt(r2));
      velocity[c] += 0.5 * acceleration[c] * deltaT;
    }
    
    // Output Data at Interval
    if (t >= tc) {
      cout << position_r[0] << " " << position_r[1] << endl;
      cerr << t << "\r";
      tc += outputTime;
    }
  }
  
  // Calculate Final System Total Energy
  e_k = 0.5 * (pow(velocity[0],2) + pow(velocity[1],2)); // Kinetic Energy
  e_p = - 1.0 / sqrt(pow(position_r[0],2) + pow(position_r[1],2)); // Potential Energy
  double e_f = e_k + e_p; // Final Energy
  
  // Calculate Error
  double error = (e_f-e_i)/e_i * 100;
  cerr << "Percentage Error: " << error << "%." << endl;
  
  return 0;
}
