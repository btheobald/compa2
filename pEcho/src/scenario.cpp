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

void scenario::updateLocalControl(sharedStage* l_sharedDataAccess) {
  UGC = l_sharedDataAccess->getUGC();
  IDT = l_sharedDataAccess->getIDT();
  IPF = l_sharedDataAccess->getIPF();
  collisions = l_sharedDataAccess->getStatus(3);
}
void scenario::updateLocalControl(double p_UGC, double p_IDT, int p_IPF, bool p_collisions) {
  UGC = p_UGC;
  IDT = p_IDT;
  IPF = p_IPF;
  collisions = p_collisions;
}

void scenario::updateSharedControl(sharedStage* l_sharedDataAccess) {
  l_sharedDataAccess->setUGC(UGC);
  l_sharedDataAccess->setIDT(IDT);
  l_sharedDataAccess->setIPF(IPF);
  l_sharedDataAccess->setStatus(3, collisions);
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
