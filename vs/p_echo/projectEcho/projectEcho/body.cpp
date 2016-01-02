#include "body.h"

// Constructors
body::body() {
}

body::body(int p_BodyID, double p_Mass, double p_Radius, float p_Color[3]) {
}

body::body(int p_BodyID, double p_Mass, double p_Radius, float p_Color[3], bool p_Fixed, double p_Position[2]) {
}

body::body(int p_BodyID, double p_Mass, double p_Radius, float p_Color[3], double p_Position, double p_Velocity[2]) {
}

// Destructor
body::~body() {
}

// Variable Access
// Return Variables
double body::getMass(void) {
  return 0.0;
}

double body::getRadius(void) {
  return 0.0;
}

bool body::getFixedStatus(void) {
  return false;
}

float body::getColor(int cIndex) {
  return 0.0f;
}

double body::getAcceleration(int xyIndex) {
  return 0.0;
}

double body::getVelocity(int xyIndex) {
  return 0.0;
}

double body::getPosition(int xyIndex) {
  return 0.0;
}

bool body::setBodyID(int p_BodyID) {
  return false;
}

bool body::setMass(double p_Mass) {
  return false;
}

bool body::setRadius(double p_Radius) {
  return false;
}

bool body::setFixed(bool p_Fixed) {
  return false;
}

bool body::setColor(float p_Color[3]) {
  return false;
}

bool body::setForce(double Force, int xyIndex) {
  return false;
}

bool body::setAcceleration(double acceleration, int xyIndex) {
  return false;
}

bool body::setVelocity(double velocity, int xyIndex) {
  return false;
}

bool body::setPosition(double position, int xyIndex) {
  return false;
}

bool body::calcAcceleration() {
  return false;
}

bool body::calcVelocity() {
  return false;
}

bool body::calcPosition() {
  return false;
}
