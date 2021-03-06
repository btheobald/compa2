#pragma once
class body
{
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
  static double timestep;

public:
  // Constructors
  body();
  body(double p_Mass, double p_Radius, float p_Color[3]);                                           // ID, Mass, Radius, Color 
  body(double p_Mass, double p_Radius, float p_Color[3], bool p_Fixed, double p_Position[2]);       // ID, Mass, Radius, Colour, Fixed, Position
  body(double p_Mass, double p_Radius, float p_Color[3], double p_Position[2], double p_Velocity[2]);  // ID, Mass, Radius, Colour, Position, Velocity
  body(double p_Mass, double p_Radius, double p_Position[2], double p_Velocity[2]);
  // Destructor
  ~body();

  // Variable Access
  // Return Variables
  double getMass(void);
  double getRadius(void);
  bool getFixedStatus(void);
  float getColor(int cIndex);
  double getAcceleration(int xyIndex);
  double getVelocity(int xyIndex);
  double getPosition(int xyIndex);

  // Set Variables (Returns OK/FAIL [0/1])
  int setMass(double p_Mass);
  int setRadius(double p_Radius);
  int setFixed(bool p_Fixed);
  int setColor(float p_Color[3]);
  int addForce(double p_Force, int xyIndex);
  int resetForce();
  int setAcceleration(double p_Acceleration, int xyIndex);
  int setVelocity(double p_Velocity, int xyIndex);
  int setPosition(double p_Position, int xyIndex);
  int setTimestep(double p_Timestep);

  // Calculate and Set (Returns OK/FAIL [0/1])
  int calcAcceleration();
  int calcHalfVelocity();
  int calcPosition();
};

