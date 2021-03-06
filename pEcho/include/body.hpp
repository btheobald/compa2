#pragma once

class body {
private:
  // Body Attributes
  double mass = 1;
  double radius = 1;
  bool fixed = false;
  float color[3] = { 0.0f, 0.0f, 0.0f };

  // Simulation Properties     X    Y
  double force[2]         = { 0.0, 0.0 };
  double acceleration[2]  = { 0.0, 0.0 };
  double velocity[2]      = { 0.0, 0.0 };
  double position[2]      = { 0.0, 0.0 };

public:
  // Constructors
  body();
  body(double p_Mass, double p_Radius, double p_PosX, double p_PosY, double p_VelX, double p_VelY, const float p_Color[3]);
  body(double p_PosX, double p_PosY);
  // Destructor
  ~body();

  // Variable Access
  // Return Variables
  double getMass(void);
  double getRadius(void);
  bool getFixedStatus(void);
  float getColor(int cIndex);
  double getAcceleration(int xyIndex);
  double getForce(int xyIndex);
  double getVelocity(int xyIndex);
  double getPosition(int xyIndex);
  double getMomentum(int xyIndex);

  // Set Variables (Returns OK/FAIL [0/1])
  void setMass(double p_Mass);
  void setRadius(double p_Radius);
  void setFixed(bool p_Fixed);
  void setColor(const float p_Color[3]);
  void addForce(double p_Force, int xyIndex);
  void resetForce();
  void setAcceleration(double p_Acceleration, int xyIndex);
  void setVelocity(double p_Velocity, int xyIndex);
  void setPosition(double p_Position, int xyIndex);

  // Calculate and Set (Returns OK/FAIL [0/1])
  void calcAcceleration();
  void calcHalfVelocity(double timestep);
  void calcPosition(double timestep);
};
