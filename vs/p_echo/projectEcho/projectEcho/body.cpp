#include "body.h"

// Constructors
body::body() {
}

body::body(double p_Mass, double p_Radius, float p_Color[3]) {
}

body::body(double p_Mass, double p_Radius, float p_Color[3], bool p_Fixed, double p_Position[2]) {
}

body::body(double p_Mass, double p_Radius, float p_Color[3], double p_Position, double p_Velocity[2]) {
}

// Destructor
body::~body() {
}

// Used in Interface
double body::getMass(void) {
  return mass;
}
double body::getRadius(void) {
  return radius;
}
bool body::getFixedStatus(void) {
  return fixed;
}
float body::getColor(int cIndex) {
  return colour[cIndex];
}
double body::getAcceleration(int xyIndex) {
  return acceleration[xyIndex];
}
double body::getVelocity(int xyIndex) {
  return velocity[xyIndex];
}
double body::getPosition(int xyIndex) {
  return position[xyIndex];
}
// Used in Setup and Interface
int body::setMass(double p_Mass) {
  mass = p_Mass;
  return 0;
}
int body::setRadius(double p_Radius) {
  radius = p_Radius;
  return 0;
}
int body::setFixed(bool p_Fixed) {
  fixed = p_Fixed;
  return 0;
}
int body::setColor(float p_Color[3]) {
  color[0] = p_Color[0];
  color[1] = p_Color[1];
  color[2] = p_Color[2];
  return 0;
}
int body::setAcceleration(double p_acceleration, int xyIndex) {
  acceleration[xyIndex] = p_acceleration;
  return 0;
}
int body::setVelocity(double p_velocity, int xyIndex) {
  velocity[xyIndex] = p_velocity;
  return 0;
}
int body::setPosition(double p_position, int xyIndex) {
  position[xyIndex] = p_position;
  return 0;
}

// Used In Simulation
int body::setForce(double p_Force, int xyIndex) {
  force[xyIndex] = p_Force;
  return 0;
}
int body::setTimestep(double p_Timestep) {
  timestep = p_Timestep;
  return 0;
}
int body::calcAcceleration() {
  for (int xy = 0; xy <= 1; xy++) {
    acceleration[xy] = force[xy] / mass;
  }
  return 0;
}
int body::calcHalfVelocity() {
  for (int xy = 0; xy <= 1; xy++) {
    velocity[xy] += acceleration[xy] * timestep * 0.5;
  }
  return 0;
}
int body::calcPosition() {
  for (int xy = 0; xy <= 1; xy++) {
    position[xy] += velocity[xy] * timestep;
  }
  return 0;
}
