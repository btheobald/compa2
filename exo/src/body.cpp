// Interface include
#include "body.hpp"

body::body() { // Creates a copy of body at pointer

}

body::body(body* p_b) { // Creates a copy of body at pointer
  // Copy contents of p_b to this object.
  *this = *p_b;
}

body::body(double p_m, double p_r, double p_pX, double p_pY, bool p_fixed) {
  // Mass
  m = p_m;
  // Radius
  r = p_r;
  // Position
  pX = p_pX;
  pY = p_pY;
  // Fixed
  fixed = p_fixed;
}

body::body(double p_m, double p_r, double p_pX, double p_pY, double p_vX, double p_vY) {
  // Mass
  m = p_m;
  // Radius
  r = p_r;
  // Position
  pX = p_pX;
  pY = p_pY;
  // Velocity
  vX = p_vX;
  vY = p_vY;
}

body::body(double p_m, double p_r, double p_pX, double p_pY, double p_vX, double p_vY, float p_color[3]) {
  // Mass
  m = p_m;
  // Radius
  r = p_r;
  // Position
  pX = p_pX;
  pY = p_pY;
  // Velocity
  vX = p_vX;
  vY = p_vY;
  // Color
  color[0] = p_color[0];
  color[1] = p_color[1];
  color[2] = p_color[2];
}

body::~body() {

}

// Calculation Methods - Requires itteration delta time
void body::calcPosition(double p_dt) {
  // ΔPosition = Velocity * ΔTime
  if(!fixed) {
    pX += vX * p_dt;
    pY += vY * p_dt;
  }
}

void body::calcHalfVelocity(double p_dt) {
  // (1/2)ΔVelocity = Acceleration * ΔTime * 0.5
  if(!fixed) {
    vX += aX * p_dt * 0.5;
    vY += aY * p_dt * 0.5;
  }
}

double body::calcMomentum(int xy) {
  // p = mv
  if(xy) {
    // Y Component
    return m * vY;
  } else {
    // X Component
    return m * vX;
  }
}
