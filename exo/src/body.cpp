#include "body.hpp"

body::body(double p_m, double p_r, double p_pX, double p_pY, bool p_fixed) {
  m = p_m;

  r = p_r;

  pX = p_pX;
  pY = p_pY;

  vX = 0;
  vY = 0;

  fixed = p_fixed;
}

body::body(double p_m, double p_r, double p_pX, double p_pY, double p_vX, double p_vY) {
  m = p_m;

  r = p_r;

  pX = p_pX;
  pY = p_pY;

  vX = p_vX;
  vY = p_vY;

  fixed = false;
}

// Calculation Methods - Requires itteration delta time
void body::calcPosiiton(double p_dt) {
  // ΔPosition = Velocity * ΔTime
  if(!fixed) {
    pX += vX * p_dt;
    pY += vY * p_dt;
  }
}

void body::calcVelocity(double p_dt) {
  // (1/2)ΔVelocity = Acceleration * ΔTime * 0.5
  if(!fixed) {
    vX += aX * p_dt * 0.5;
    vY += aY * p_dt * 0.5;
  }
}

double body::calcMomentum(int xy); {
  // p = mv
  if(xy) {
    // Y Component
    return m * vY;
  } else {
    // X Component
    return m * vX;
  }
}
