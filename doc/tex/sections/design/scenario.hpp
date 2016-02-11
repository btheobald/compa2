class scenario {
protected:
  // Body Storage
  vector<body> bodyStore

  // Status Register (Set Internally)
  uint8_t sreg;

  // Main Sim Control Variables
  double gravConst;
  double deltaTime;
  int itrPerFrm;

public:
  scenario();
  ~scenario();

  // Returns Bit 0-7 on sreg.
  bool getSReg(int p_bit);

  // Body Management
  void newBody(double p_mass, double p_radius, double p_position[2], double p_velocity[2]);
  void delBody(int p_bodyID);

  // Shared Access Methods
  void updateSharedControl(sharedStage* p_sharedAccess);
  void updateSharedBody(sharedStage* p_sharedAccess);
  void updateLocalControl(sharedStage* p_sharedAccess);
  void updateLocalBody(sharedStage* p_sharedAccess);
};
