#pragma once

class body {
private:
  float m;      // Mass
  float a[2]; // Acceleration
  float v[2]; // Velocity
  float p[2]; // Position

public:
  body();
  body(float p_mass, float p_posX, float p_posY, float p_velX, float p_velY);
  ~body();

  double getPos(int index);
};
