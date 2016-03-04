#pragma once
// Standard Library Includes
#include <mutex>
#include <condition_variable>
// Custom Includes
#include "body.hpp"
#include "com.hpp"

class sharedStage {
private:
  // Body Storage
  com::bodyVector bodyStore_R;
  com::bodyVector bodyStore_S;

  // Simulation Control
  double UGC;     // Simulation Universal Gravitational Constant
  double IDT;     // Simulation Itteration Delta Time
  int IPF;        // Simulation Itterations per Render Frame

  // Runtime Control
  bool pause;     // Pause Signal
  bool exit;      // Exit Signal
  bool exitAck;   // ExitAck Signal

  // Flow Control
  bool newRScenario;  // New Render Data Set
  bool newSScenario;  // New Sim Data Set

  // Mutex Lock Objects
  std::mutex bStoreR_Lock;
  std::mutex bStoreS_Lock;
  std::mutex UGC_Lock;
  std::mutex IDT_Lock;
  std::mutex IPF_Lock;
  std::mutex pause_Lock;
  std::mutex exit_Lock;
  std::mutex exitAck_Lock;
  std::mutex newRS_Lock;
  std::mutex newSS_Lock;

public:

  sharedStage();
  ~sharedStage();

  void populateBodyStore_R(com::bodyVector p_BodyStore);
  void populateBodyStore_S(com::bodyVector p_BodyStore);
  com::bodyVector returnBodyStore_R();
  com::bodyVector returnBodyStore_S();

  void setUGC(double var);
  void setIDT(double var);
  void setIPF(int var);

  double getUGC();
  double getIDT();
  int getIPF();

  bool newRScenarioCheck();
  bool newSScenarioCheck();

  std::condition_variable simWait;

  // 0 : Pause, 1 : Exit, 2 : ExitAck
  void setStatus(int var, bool set);
  bool getStatus(int var);
};
