#include <iostream>
#include "body.hpp"

body::body(){
}

body::body(float p_mass, float p_posX, float p_posY, float p_velX, float p_velY) {
  mass = p_mass;

  pos[0] = p_posX;
  pos[1] = p_posY;

  vel[0] = p_velX;
  vel[1] = p_velY;
}

body::~body(){
}
