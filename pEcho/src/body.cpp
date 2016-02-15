#include "body.hpp"

// Constructors
body::body() {
  mass = 1;
  radius = 1;

  position[0] = 0;
  position[0] = 0;

  velocity[0] = 0;
  velocity[0] = 0;
}

body::body(float p_Mass, float p_Radius, float p_PosX, float p_PosY, float p_VelX, float p_VelY, const float p_Color[3]) {
  mass = p_Mass;
  radius = p_Radius;
  // Set Position
  position[0] = p_PosX;
  position[1] = p_PosY;
  // Set Velocity
  velocity[0] = p_VelX;
  velocity[1] = p_VelY;
  // Set Colour
  color[0] = p_Color[0];
  color[1] = p_Color[1];
  color[2] = p_Color[2];
}

body::body(float p_PosX, float p_PosY) {
  mass = 100;
  radius = 1;
  // Set Position
  position[0] = p_PosX;
  position[1] = p_PosY;
  // Set Velocity
  velocity[0] = 0;
  velocity[1] = 0;
}

// Destructor
body::~body() {
}

// Used in Interface
float body::getMass(void) {
  return mass;
}
float body::getRadius(void) {
  return radius;
}
bool body::getFixedStatus(void) {
  return fixed;
}
float body::getColor(int cIndex) {
  return color[cIndex];
}
float body::getAcceleration(int xyIndex) {
  return acceleration[xyIndex];
}
float body::getVelocity(int xyIndex) {
  return velocity[xyIndex];
}
float body::getPosition(int xyIndex) {
  return position[xyIndex];
}
float body::getMomentum(int xyIndex) {
  return mass * velocity[xyIndex];
}
// Used in Setup and Interface
void body::setMass(float p_Mass) {
  mass = p_Mass;
}
void body::setRadius(float p_Radius) {
  radius = p_Radius;
}
void body::setFixed(bool p_Fixed) {
  fixed = p_Fixed;
}
void body::setColor(const float p_Color[3]) {
  color[0] = p_Color[0];
  color[1] = p_Color[1];
  color[2] = p_Color[2];
}
void body::setAcceleration(float p_acceleration, int xyIndex) {
  acceleration[xyIndex] = p_acceleration;
}
void body::setVelocity(float p_velocity, int xyIndex) {
  velocity[xyIndex] = p_velocity;
}
void body::setPosition(float p_position, int xyIndex) {
  position[xyIndex] = p_position;
}

// Used In Simulation
void body::addForce(float p_Force, int xyIndex) {
  force[xyIndex] = force[xyIndex] + p_Force;
}
void body::resetForce() {
  force[0] = 0;
  force[1] = 0;
}

void body::calcAcceleration() {
  acceleration[0] = force[0] / mass;
  acceleration[1] = force[1] / mass;
}
void body::calcHalfVelocity(float timestep) {
  velocity[0] = velocity[0] + ( acceleration[0] * (timestep * 0.5) );
  velocity[1] = velocity[1] + ( acceleration[1] * (timestep * 0.5) );
}
void body::calcPosition(float timestep) {
  position[0] = position[0] + ( velocity[0] * timestep );
  position[1] = position[1] + ( velocity[1] * timestep );
}
