#include <iostream>
#include <cmath>

/*  
 *  # Calculate Force
 *  F = (GmM)/d^2 ((Gravitational Constant * Mass-1 * Mass-2) / Distance^2)
 *  # Resolve Vectors
 *  Fx = FcosA
 *  Fy = FsinA
 *  # Calcualate Acceleration
 *  a = F/m (Acceleration = Force / Mass)
 *  # Calcualate Change in Velocity
 *  tf * a = dv (Time per Frame * Acceleration = Change in Velocity)
 *  # Calculate Change in Position
 *  tf * v = dP (Time per Frame * Velocity = Change in Position)
 *  # Calculate New Position
 */

// Prototypes
// Resolve Vectors
double resolveX(double force, double angle);
double resolveY(double force, double angle);
// Newtons Second Law (Flexible Function)
double nsl(double force = NULL; double mass = NULL, double accel = NULL);

// Functions
int main() {

}



double nsl(double force = NULL; double mass = NULL, double accel = NULL) {
  double result = 0;
  // Check for NULL parameter
  if(force == NULL & mass != NULL & accel != NULL)
    result = mass * accel;
  if(force != NULL & mass == NULL & accel != NULL)
    result = force / accel;
  if(force != NULL & mass != NULL & accel == NULL)
    result = force / mass;
  // If more than one parameter is NULL 0 is returned.
  return result;
}
