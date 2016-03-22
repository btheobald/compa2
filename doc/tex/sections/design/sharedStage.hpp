class sharedStage {
private:
  // Body Storage
  vector<body> sharedSimBodyStore;
  vector<body> sharedRdrBodyStore;

  // Simulation Control
  double gravConst;     // Simulation Universal Gravitational Constant
  double deltaTime;     // Simulation Itteration Delta Time
  int itrPerFrm;        // Simulation Itterations per Render Frame

  // Runtime Control
  bool pause;     // Pause Signal

  // Flow Control
  bool newDataSim;  // New Data for Sim
  bool newDataRdr;  // New Data for Render

  // Mutex Lock Objects
  std::mutex sBStore_Lock;
  std::mutex gravConst_Lock;
  std::mutex deltaTime_Lock;
  std::mutex itrPerFrm_Lock;
  std::mutex pause_Lock;
  std::mutex newData_Lock;

public:
  sharedStage();
  ~sharedStage();

  // Set/Get Body Store (Render <-> Sim) (Locking)
  void populateBStore(vector<body> p_BodyStore, int p_rs);
  vector<body> returnSBStore(int p_rs);

  // Set/Get Sim Control (Locking)
  void setGravConst(double var);
  void setDeltaTime(double var);
  void setItrPerFrm(int var);
  double getGravConst();
  double getDeltaTime();
  int getItrPerFrm();

  // Return True if New Data Avaliable (Locking)
  bool newDataCheck();

  // Set/Get Pause (Locking)
  void setPause(bool set);
  bool getPause();
};
