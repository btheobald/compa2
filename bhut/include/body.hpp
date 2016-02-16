#pragma once
#include <iostream>

class body {
private:
  int id;     // Body ID
  float m;    // Mass
  float a[2]; // Acceleration
  float v[2]; // Velocity
  float p[2]; // Position

public:
  body();
  body(float p_mass, float p_posX, float p_posY, float p_velX, float p_velY, int p_id);
  ~body();

  inline double getP(int index) {return p[index];}
  inline double getM() {return m;};
  inline int getID() {return id;};
};
