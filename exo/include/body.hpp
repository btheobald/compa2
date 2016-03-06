class body {
private:

public:
  // Parameters - Not encapsulated, makes interface and use easier
  double m;       // Mass - kg
  double r;       // Radius - m
  double pX, pY;  // Position - Base Unit - m
  double vX, vY;  // Velocity - First Derrirative - ms^-1
  double aX, aY;  // Acceleration - Second Derrative ms^-2

  // Memory ineffcient - minimum allocation is 1 byte, not 1 bit.
  bool fixed;     // Fixed

  // Constructors
  body(double p_m, double p_r, double p_pX, double p_pY);
  body(double p_m, double p_r, double p_pX, double p_pY, double p_vX, double p_vY);
  // Destructor
  ~body();

  // Calculation Methods - Requires itteration delta time
  void calcPosiiton(double p_dt); // Calculate new position based on current velocity
  void calcHalfVelocity(double p_dt); // Calculate new velocity based on current acceleration (Half Timestep)

  double calcMomentum(int xy); // Calculate momentum and return component, used in collisions
};
