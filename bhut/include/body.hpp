#pragma once

class body {
private:
  float m;      // Mass
  float aX, aY; // Acceleration
  float vX, vY; // Velocity
  float pX, pY; // Position

public:
  body();
  body(float p_mass, float p_posX, float p_posY, float p_velX, float p_velY);
  ~body();
};
