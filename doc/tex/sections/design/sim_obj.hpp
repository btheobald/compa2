class sim_obj : public scenario {
private:
  double calcCompDistance(int bodyID_A, int bodyID_B, int xy);
  double calcVectDistance(double distX, double distY);

  // 2D Body Matrix
  vector<vector<body>> forceMatrix;
  double calcForceBodyPair(int bodyID_A, int bodyID_B, double distV);
  void calcForceMatrix();
  void calcForceSumAB();

  void calcAcceleraitonAB();
  void calcHalfVelocityAB();
  void calcPositionAB();
  void calcCollision();

public:
  sim_obj();
  ~sim_obj();
  void itteration();
};
