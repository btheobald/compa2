// Header Include
#include "sharedStage.hpp"

sharedStage::sharedStage() {
  pause = true;
  exit = false;
  exitAck = false;
}
sharedStage::~sharedStage(){

}

void sharedStage::populateBodyStore_R(com::bodyVector p_BodyStore) {
  newRS_Lock.lock();
  if(newRScenario == false) {
    bStoreR_Lock.lock();
    bodyStore_R = p_BodyStore;
    bStoreR_Lock.unlock();

    newRScenario = true;

    //cerr << "Render > Share" << endl;
  }
  newRS_Lock.unlock();
}

void sharedStage::populateBodyStore_S(com::bodyVector p_BodyStore) {
  newSS_Lock.lock();
  if(newSScenario == false) {
    bStoreS_Lock.lock();
    bodyStore_S = p_BodyStore;
    bStoreS_Lock.unlock();

    newSScenario = true;

    //cerr << "Sim > Share" << endl;
  }
  newSS_Lock.unlock();
}

com::bodyVector sharedStage::returnBodyStore_R() {
  com::bodyVector tempStore;
  newRS_Lock.lock();
  bStoreR_Lock.lock();
  tempStore = bodyStore_R;
  bStoreR_Lock.unlock();

  newRScenario = false;

  //cerr << "Share > Sim" << endl;

  newRS_Lock.unlock();
  return tempStore;
}

com::bodyVector sharedStage::returnBodyStore_S() {
  com::bodyVector tempStore;
  newSS_Lock.lock();
  bStoreS_Lock.lock();
  tempStore = bodyStore_S;
  bStoreS_Lock.unlock();

  newSScenario = false;

  //cerr << "Share > Render" << endl;

  newSS_Lock.unlock();
  return tempStore;
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

bool sharedStage::newRScenarioCheck() {
  bool tempStore;
  newRS_Lock.lock();
  tempStore = newRScenario;
  newRS_Lock.unlock();
  return tempStore;
}

bool sharedStage::newSScenarioCheck() {
  bool tempStore;
  newSS_Lock.lock();
  tempStore = newSScenario;
  newSS_Lock.unlock();
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
    default:
      localTemp = false;
  }
  return localTemp;
}
