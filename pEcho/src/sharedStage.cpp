#include "sharedStage.hpp"

sharedStage::sharedStage() {
  pause = true;
  exit = false;
  exitAck = false;
}
sharedStage::~sharedStage(){

}

void sharedStage::populateBodyStore_R(vector<body> p_BodyStore) {
  bStoreR_Lock.lock();
  bodyStore_R = p_BodyStore;
  bStoreR_Lock.unlock();
}

void sharedStage::populateBodyStore_S(vector<body> p_BodyStore) {
  bStoreS_Lock.lock();
  bodyStore_S = p_BodyStore;
  bStoreS_Lock.unlock();
}

vector<body> sharedStage::returnBodyStore_R() {
  bStoreR_Lock.lock();
  vector<body> tempStore = bodyStore_R;
  bStoreR_Lock.unlock();

  return tempStore;
}

vector<body> sharedStage::returnBodyStore_S() {
  bStoreS_Lock.lock();
  vector<body> tempStore = bodyStore_S;
  bStoreS_Lock.unlock();

  return bodyStore_S;
}

void setSimUGC(double var) {
  simUGC_Lock.lock();
  simUGC = var;
  simUGC_Lock.unlock();
}
void setSimIDT(double var) {
  simIDT_Lock.lock();
  simIDT = var;
  simIDT_Lock.unlock();
}
void setSimIPF(int var) {
  simIPF_Lock.lock();
  simIPF = var;
  simIPF_Lock.lock();
}

double getSimUGC() {
  double tempStore;
  simUGC_Lock.lock();
  tempStore = simUGC;
  simUGC_Lock.unlock();

  return tempStore;
}
double getSimIDT() {
  double tempStore;
  simIDT_Lock.lock();
  tempStore = simIDT;
  simIDT_Lock.unlock();

  return tempStore;
}
int getSimIPF() {
  int tempStore;
  simIPF_Lock.lock();
  tempStore = simIPF;
  simIPF_Lock.unlock();

  return tempStore;
}

void sharedStage::setStatus(bool set, int var) {
  switch(var) {
    case 0:
      pause_Lock.lock();
      pause = set;
      pause_Lock.unlock();
      break;
    case 1:
      exit_Lock.lock();
      exit = set;
      exit_Lock.unlock();
      break;
  }
}
bool sharedStage::getStatus(int var) {
  bool localTemp;
  switch(var) {
    case 0:
      pause_Lock.lock();
      localTemp = pause;
      pause_Lock.unlock();
      break;
    case 1:
      exit_Lock.lock();
      localTemp = exit;
      exit_Lock.unlock();
      break;
  }
  return localTemp;
}
