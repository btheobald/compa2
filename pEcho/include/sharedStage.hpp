#pragma once
#include <vector>
#include <mutex>
#include "body.h"
using namespace std;

class sharedStage {
private:
  // Body Storage
  vector<body> bodyStore_R;
  vector<body> bodyStore_S;

  // Simulation Control
  double simUGC; // Simulation Universal Gravitational Constant
  double simIDT; // Simulation Itteration Delta Time
  int simIPF;    // Simulation Itterations per Render Frame

  // Runtime Control
  bool pause; // Pause Signal
  bool exit; // Exit Signal
  bool exitAck; // Simulation Acknowleges Exit

  // Mutex Lock Objects
  mutex bStoreR_Lock;
  mutex bStoreS_Lock;
  mutex simUGC_Lock;
  mutex simIDT_Lock;
  mutex simIPF_Lock;
  mutex pause_Lock;
  mutex exit_Lock;

public:
  sharedStage();
  ~sharedStage();

  void populateBodyStore_R(vector<body> p_BodyStore);
  void populateBodyStore_S(vector<body> p_BodyStore);
  vector<body> returnBodyStore_R();
  vector<body> returnBodyStore_S();
};
