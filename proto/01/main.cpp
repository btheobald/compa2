#include <iostream>
#include <cmath>
#include <unistd.h>

#define GRAVCONST 6.67E-11
#define TIMESTEP 60

using namespace std;

/*  
 *  # Calculate Force
 *  F = (GmM)/d^2 ((Gravitational Constant * Mass-1 * Mass-2) / Distance^2)
 *  # Resolve Vectors
 *  Fx = FcosA
 *  Fy = FsinA
 *  # Calculate Acceleration
 *  a = F/m (Acceleration = Force / Mass)
 *  # Calculate Change in Velocity
 *  tf * a = dv (Time per Frame * Acceleration = Change in Velocity)
 *  # Calculate Change in Position
 *  tf * v = dP (Time per Frame * Velocity = Change in Position)
 *  # Calculate New Position
 */
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
double calcDistance(bodyPair calcBodyPair);
double gravForce(double G, double m_1, double m_2, double d);
// Calculate the Angle of a vector bettween two bodies relative to global axis.
double calcAngle(bodyPair calcBodyPair);
// Resolve Vectors
double resolveX(double force, double angle);
double resolveY(double force, double angle);
// Newtons Second Law (Flexible Function)
double nsl(double force, double mass, double accel);

// Functions
int main() {
  bodyPair currentBodies;
  int i, xy, tracker = 0;
  double currentForce, currentAngle;
  
  // Sol
  currentBodies[0].mass = 1.989E30;
  currentBodies[0].position[0] = 0.0;
  currentBodies[0].position[1] = 0.0;
  // Mercury
  currentBodies[1].mass = 3.285E23;
  currentBodies[1].position[0] = 50E8;
  currentBodies[1].position[1] = 0.0;
  currentBodies[1].velocity[0] = 0.0;
  currentBodies[1].velocity[1] = 47E3;
  
  while (1) {
    // Calculate Force
    currentForce = gravForce(GRAVCONST, currentBodies[0].mass, currentBodies[1].mass, calcDistance(currentBodies));
    // Find Angle (Rad)
    currentAngle = calcAngle(currentBodies);

    // Resolve Forces
    currentBodies[0].force[0] = resolveX(currentForce, currentAngle);
    currentBodies[0].force[1] = resolveY(currentForce, currentAngle);
    currentBodies[1].force[0] = resolveX(-currentForce, -currentAngle);
    currentBodies[1].force[1] = resolveY(-currentForce, -currentAngle);

    // Calculate Acceleration
    for(i = 0; i < 2; i++) {
      for(xy = 0; xy < 2; xy++) {
        currentBodies[i].acceleration[xy] = nsl(currentBodies[i].force[xy], currentBodies[i].mass, NULL);
      }
    }

    // Calculate Change in Velocity
    for(i = 0; i < 2; i++) {
      for(xy = 0; xy < 2; xy++) {
        currentBodies[i].velocity[xy] += currentBodies[i].acceleration[xy] * TIMESTEP; 
      }
    }
    
    // Calculate Change in Position
    for(i = 0; i < 2; i++) {
      for(xy = 0; xy < 2; xy++) {
        currentBodies[i].position[xy] += currentBodies[i].velocity[xy] * TIMESTEP; 
      }
    }
    
    cout << currentBodies[1].position[0] << " " << currentBodies[1].position[1] << endl;
    usleep(10000);
  }
}

double calcDistance(bodyPair calcBodyPair) {
  double distance, x, y;
  
  double b0posX = calcBodyPair[0].position[0];
  double b0posY = calcBodyPair[0].position[1];
  double b1posX = calcBodyPair[1].position[0];
  double b1posY = calcBodyPair[1].position[1]; 
  
  x = abs(b0posX - b1posX);
  y = abs(b0posY - b1posY);

  double stage1 = pow(x, 2.0) + pow(y, 2.0);
  distance = sqrt(stage1);
  
  return distance;
}

double gravForce(double G, double m_1, double m_2, double d) {
  // F = (GmM)/d^2
  double result;
  double top;
  
  top = G * m_1 * m_2;
  
  result = top/pow(d, 2.0);
  return result;
}

double calcAngle(bodyPair calcBodyPair) {
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

double nsl(double force, double mass, double accel) {
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
