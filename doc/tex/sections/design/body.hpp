class body {
private:
  // Parameters
  int id;
  double mass;
  double radius;
  float colour[3];
  bool fixed;
  // Properties
  double force[2];
  double acceleration[2];
  double velocity[2];
  double position[2];

public:
  // Constructor
  body(double p_mass, double p_radius, double p_position[2], double p_velocity[2]);
  // Destructor
  ~body();

  // Encapsulation Methods
  // Get
  double getMass();
  double getRadius();
  float getColor(int p_cpIndex);
  bool getFixed();
  double getAcceleration(int p_xyIndex);
  double getVelocity(int p_xyIndex);
  double getPosition(int p_xyIndex);
  // Set
  void setID(int p_id);
  void setMass(double p_mass);
  void setRadius(double p_radius);
  void setColor(float p_r, float p_g, float p_b);
  void setFixed(bool p_fixed);
  void setForce(double p_force, int p_xyIndex);
  void setAcceleration(double p_acceleration, int p_xyIndex);
  void setVelocity(double p_velocity, int p_xyIndex);
  void setPosition(double p_position, int p_xyIndex);
  // Calculate
  void calcAcceleration(int p_xyIndex);
  void calcVelocity(int p_xyIndex);
  void calcPosition(int p_xyIndex);
}
