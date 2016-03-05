// Header Include
#include "sharedStage.hpp"
#include <iostream>

sharedStage::sharedStage() {
  pause = true;
  exit = false;
  exitAck = false;
  collisions = false;
}
sharedStage::~sharedStage(){

}

void sharedStage::populateBodyStore_R(com::bodyVector p_BodyStore) {
  com::lockGuard lockNewStatus(newRS_Lock);
  if(newRScenario == false) {
    com::lockGuard lockAccess(bStoreR_Lock);
    bodyStore_R = p_BodyStore;

    newRScenario = true;
    //cerr << "Render > Share" << endl;
  }
}

void sharedStage::populateBodyStore_S(com::bodyVector p_BodyStore) {
  com::lockGuard lockNewStatus(newSS_Lock);
  if(newSScenario == false) {
    com::lockGuard lockAccess(bStoreS_Lock);
    bodyStore_S = p_BodyStore;

    newSScenario = true;
    //cerr << "Sim > Share" << endl;
  }
}

com::bodyVector sharedStage::returnBodyStore_R() {
  com::lockGuard lockNewStatus(newRS_Lock);
  com::lockGuard lockAccess(bStoreR_Lock);

  newRScenario = false;
  //cerr << "Share > Sim" << endl;

  return bodyStore_R;
}

com::bodyVector sharedStage::returnBodyStore_S() {
  com::lockGuard lockNewStatus(newSS_Lock);
  com::lockGuard lockAccess(bStoreS_Lock);

  newSScenario = false;
  //cerr << "Share > Render" << endl;

  return bodyStore_S;
}

void sharedStage::setUGC(double var) {
  com::lockGuard lockAccess(UGC_Lock);
  UGC = var;
}
void sharedStage::setIDT(double var) {
  com::lockGuard lockAccess(IDT_Lock);
  IDT = var;
}
void sharedStage::setIPF(int var) {
  com::lockGuard lockAccess(IPF_Lock);
  IPF = var;
}

double sharedStage::getUGC() {
  com::lockGuard lockAccess(UGC_Lock);
  return UGC;
}
double sharedStage::getIDT() {
  com::lockGuard lockAccess(IDT_Lock);
  return IDT;
}
int sharedStage::getIPF() {
  com::lockGuard lockAccess(IPF_Lock);
  return IPF;
}

bool sharedStage::newRScenarioCheck() {
  com::lockGuard lockNewStatus(newRS_Lock);
  return newRScenario;
}

bool sharedStage::newSScenarioCheck() {
  com::lockGuard lockNewStatus(newSS_Lock);
  return newSScenario;
}

void sharedStage::setStatus(int var, bool set) {
  switch(var) {
    case 0: {
      com::lockGuard lockAccess(pause_Lock);
      pause = set;
      break;
    }
    case 1: {
      com::lockGuard lockAccess(exit_Lock);
      exit = set;
      break;
    }
    case 2: {
      com::lockGuard lockAccess(exitAck_Lock);
      exitAck = set;
      break;
    }
    case 3: {
      com::lockGuard lockAccess(collision_Lock);
      collisions = set;
      break;
    }
  }
}

bool sharedStage::getStatus(int var) {
  switch(var) {
    case 0: {
      com::lockGuard lockAccess(pause_Lock);
      return pause;
    }
    case 1: {
      com::lockGuard lockAccess(exit_Lock);
      return exit;
    }
    case 2: {
      com::lockGuard lockAccess(exitAck_Lock);
      return exitAck;
    }
    case 3: {
      com::lockGuard lockAccess(collision_Lock);
      return collisions;
    }
    default: return true;
  }
}
