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
  body(float p_m, float p_pX, float p_pY, float p_vX, float p_vY, int p_id);
  ~body();

  inline double getP(int index) {return p[index];}
  inline double getM() {return m;};
  inline int getID() {return id;};
};
