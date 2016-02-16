#include "body.hpp"

body::body(){
}

body::body(float p_m, float p_pX, float p_pY, float p_vX, float p_vY, int p_id) {
  m = p_m;

  p[0] = p_pX;
  p[1] = p_pY;

  v[0] = p_vX;
  v[1] = p_vY;

  id = p_id;
}

body::~body(){
}
