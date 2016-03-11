#pragma once

class body {
private:

public:
  // Parameters - Not encapsulated, code is neater, encapsulation makes interface difficult.
  double m = 0;       // Mass - kg
  double r = 0;       // Radius - m
  double pX = 0, pY = 0;  // Position - Base Unit - m
  double vX = 0, vY = 0;  // Velocity - First Derrirative - ms^-1
  double aX = 0, aY = 0;  // Acceleration - Second Derrative ms^-2

  // Memory ineffcient - minimum allocation is 1 byte, not 1 bit, not much can be done about this.
  bool fixed = false;     // Fixed

  // Colour array
  float color[3] = { 1.0f, 1.0f, 1.0f };

  // Constructors
  body(); // Null body
  body(body* p_b); // Creates a copy of body at pointer
  body(double p_m, double p_r, double p_pX, double p_pY, bool p_fixed);
  body(double p_m, double p_r, double p_pX, double p_pY, double p_vX, double p_vY);
  // Destructor
  ~body();

  // Calculation Methods - Requires itteration delta time
  void calcPosition(double p_dt); // Calculate new position based on current velocity
  void calcHalfVelocity(double p_dt); // Calculate new velocity based on current acceleration (Half Timestep)

  double calcMomentum(int xy); // Calculate momentum and return component, used in collisions
};
