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

}

vector<body> sharedStage::returnBodyStore_R() {
  bStoreR_Lock.lock();
  vector<body> tempStore = bodyStore_R;
  bStoreR_Lock.unlock();

  return tempStore;
}

vector<body> sharedStage::returnBodyStore_S() {
  return bodyStore_S;
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
