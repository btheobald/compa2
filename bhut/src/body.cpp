#include "body.hpp"

body::body(){
}

body::body(float p_m, float p_pX, float p_pY, float p_vX, float p_vY) {
  m = p_m;

  p[0] = p_pX;
  p[1] = p_pY;

  v[0] = p_vX;
  v[1] = p_vY;
}

body::~body(){
}

body body::operator+(const body& b) {
  body t;
  t.m = this->m + b.m;
  t.p[0] = ((this->m * this->p[0]) + (b.m * b.p[0])) / t.m;
  t.p[1] = ((this->m * this->p[1]) + (b.m * b.p[1])) / t.m;
  return t;
}
