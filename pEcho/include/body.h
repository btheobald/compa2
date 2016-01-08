#pragma once
class body
{
private:
  // Body Attributes
  int bodyID;
  double mass = 0.0;
  double radius = 0.0;
  bool fixed = false;
  float colour[3] = { 0.0f, 0.0f, 0.0f };
  
  // Simulation Properties     X    Y
  double force[2]         = { 0.0, 0.0 };
  double acceleration[2]  = { 0.0, 0.0 };
  double velocity[2]      = { 0.0, 0.0 };
  double position[2]      = { 0.0, 0.0 };

public:
  // Constructors
  body();
  body(int p_BodyID, double p_Mass, double p_Radius, float p_Color[3]);                                           // ID, Mass, Radius, Color 
  body(int p_BodyID, double p_Mass, double p_Radius, float p_Color[3], bool p_Fixed, double p_Position[2]);       // ID, Mass, Radius, Colour, Fixed, Position
  body(int p_BodyID, double p_Mass, double p_Radius, float p_Color[3], double p_Position, double p_Velocity[2]);  // ID, Mass, Radius, Colour, Position, Velocity
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
  bool setBodyID(int p_BodyID);
  bool setMass(double p_Mass);
  bool setRadius(double p_Radius);
  bool setFixed(bool p_Fixed);
  bool setColor(float p_Color[3]);
  bool setForce(double p_Force, int xyIndex);
  bool setAcceleration(double p_Acceleration, int xyIndex);
  bool setVelocity(double p_Velocity, int xyIndex);
  bool setPosition(double p_Position, int xyIndex);

  // Calculate and Set (Returns OK/FAIL [0/1])
  bool calcAcceleration();
  bool calcVelocity();
  bool calcPosition();
};

