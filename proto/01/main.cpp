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
// Types 
typedef struct {
  // Properties
  double mass;
  // State
  double force[2];
  double acceleration[2];
  double velocity[2];
  double position[2];
} sBody; // Single Body;

typedef sBody[2] bodyPair;
typedef sBody[8] scenario;

// Prototypes
double gravForce(double G, double m_1, double m_2, double d);
// Calculate the Angle of a vector bettween two bodies relative to global axis.
double calcAngle(double angle, bodyPair calcBodyPair);
// Resolve Vectors
double resolveX(double force, double angle);
double resolveY(double force, double angle);
// Newtons Second Law (Flexible Function)
double nsl(double force = NULL; double mass = NULL, double accel = NULL);

// Functions
int main() {

}

double gravForce(double G, double m_1, double m_2, double d) {

}

double calcAngle(double angle, bodyPair calcBodyPair) {
  // Tan(O/A);
  double b0posX = calcBodyPair[0].position[0];
  double b0posY = calcBodyPair[0].position[1];
  double b1posX = calcBodyPair[1].position[0];
  double b1posY = calcBodyPair[1].position[1]; 
  
  double opp, adj;
  double result;
  
  adj = abs(b0posX - b1posX);
  opp = abs(b0posY - b1posY);
  
  result = atan(opp/adj);
  
  return result;
}

double resolveX(double force, double angle) {
  // Fx = FcosA
  double result;
  result = force * cos(angle);
  return result;
}

double resolveY(double force, double angle) {
  // Fy = FsinA
  double result;
  result = force * sin(angle);
  return result;
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
