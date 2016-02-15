#pragma once

class body {
private:
  // Body Attributes
  float mass = 1;
  float radius = 1;
  bool fixed = false;
  float color[3] = { 0.0f, 0.0f, 0.0f };

  // Simulation Properties     X    Y
  float force[2]         = { 0.0, 0.0 };
  float acceleration[2]  = { 0.0, 0.0 };
  float velocity[2]      = { 0.0, 0.0 };
  float position[2]      = { 0.0, 0.0 };

public:
  // Constructors
  body();
  body(float p_Mass, float p_Radius, float p_PosX, float p_PosY, float p_VelX, float p_VelY, const float p_Color[3]);
  body(float p_PosX, float p_PosY);
  // Destructor
  ~body();

  // Variable Access
  // Return Variables
  float getMass(void);
  float getRadius(void);
  bool getFixedStatus(void);
  float getColor(int cIndex);
  float getAcceleration(int xyIndex);
  float getVelocity(int xyIndex);
  float getPosition(int xyIndex);
  float getMomentum(int xyIndex);

  // Set Variables (Returns OK/FAIL [0/1])
  void setMass(float p_Mass);
  void setRadius(float p_Radius);
  void setFixed(bool p_Fixed);
  void setColor(const float p_Color[3]);
  void addForce(float p_Force, int xyIndex);
  void resetForce();
  void setAcceleration(float p_Acceleration, int xyIndex);
  void setVelocity(float p_Velocity, int xyIndex);
  void setPosition(float p_Position, int xyIndex);

  // Calculate and Set (Returns OK/FAIL [0/1])
  void calcAcceleration();
  void calcHalfVelocity(float timestep);
  void calcPosition(float timestep);
};
