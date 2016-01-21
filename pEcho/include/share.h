#pragma once
#include <vector>
#include <mutex>
#include "body.h"

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
  bool pause // Pause Signal
  bool exit // Exit Signal
  bool exitAck; // Simulation Acknowleges Exit

  // Mutex Lock Objects
  mutex simUGC_Lock;
  mutex simIDT_Lock;
  mutex simIPF_Lock;
  mutex pause_Lock;
  mutex exit_Lock;
  mutex exitAck_Lock;

public:
  void populateBodyStore_R(double* p_BodyStore) {

  }
  void populateBodyStore_S(double* p_BodyStore) {

  }
  void populateBodyStore_R(double* p_BodyStore) {

  }

  void setSimUGC(double p_UGC) {

  }
};
