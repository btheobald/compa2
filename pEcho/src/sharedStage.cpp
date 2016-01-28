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

void sharedStage::setUGC(double var) {
  UGC_Lock.lock();
  UGC = var;
  UGC_Lock.unlock();
}
void sharedStage::setIDT(double var) {
  IDT_Lock.lock();
  IDT = var;
  IDT_Lock.unlock();
}
void sharedStage::setIPF(int var) {
  IPF_Lock.lock();
  IPF = var;
  IPF_Lock.unlock();
}

double sharedStage::getUGC() {
  double tempStore;
  UGC_Lock.lock();
  tempStore = UGC;
  UGC_Lock.unlock();

  return tempStore;
}
double sharedStage::getIDT() {
  double tempStore;
  IDT_Lock.lock();
  tempStore = IDT;
  IDT_Lock.unlock();

  return tempStore;
}
int sharedStage::getIPF() {
  int tempStore;
  IPF_Lock.lock();
  tempStore = IPF;
  IPF_Lock.unlock();

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
