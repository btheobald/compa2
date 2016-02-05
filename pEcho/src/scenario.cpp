// Header Include
#include "scenario.hpp"

scenario::scenario() {

}

scenario::~scenario() {

}

void scenario::newBody(double p_Mass, double p_Radius, double p_PosX, double p_PosY, double p_VelX, double p_VelY, const float p_Color[3]) {
  bodyStore.push_back(std::move(body(p_Mass, p_Radius, p_PosX, p_PosY, p_VelX, p_VelY, p_Color)));
}
void scenario::delBody(int index) {
  bodyStore.erase(bodyStore.begin() + index);
}
void scenario::delAllBodies(int index) {
  bodyStore.clear();
}
void scenario::populateBodyStore(com::bodyVector tempStore) {
  bodyStore = tempStore;
}
com::bodyVector scenario::returnBodyStore() {
  return bodyStore;
}

void scenario::updateControl(sharedStage* l_sharedDataAccess) {
  UGC = l_sharedDataAccess->getUGC();
  IDT = l_sharedDataAccess->getIDT();
  IPF = l_sharedDataAccess->getIPF();
}

double scenario::getUGC() {
  return UGC;
}
double scenario::getIDT() {
  return IDT;
}
int scenario::getIPF() {
  return IPF;
}
