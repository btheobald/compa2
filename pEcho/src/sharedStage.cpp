#include "sharedStage.hpp"

sharedStage::sharedStage() {

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
