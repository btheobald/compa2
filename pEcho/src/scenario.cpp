// Header Include
#include "scenario.hpp"

scenario::scenario() {

}

scenario::~scenario() {

}

void scenario::newBody(double p_Mass, double p_Radius, double p_PosX, double p_PosY, double p_VelX, double p_VelY) {
  bodyStore.push_back(std::move(body(p_Mass, p_Radius, p_PosX, p_PosY, p_VelX, p_VelY)));
}
void scenario::newBody(double p_PosX, double p_PosY) {
  bodyStore.push_back(std::move(body(p_PosX, p_PosY)));
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

void scenario::setUGC(double p_UGC) {
  UGC = p_UGC;
}
void scenario::setIDT(double p_IDT) {
  IDT = p_IDT;
}
void scenario::setIPF(int p_IPF) {
  IPF = p_IPF;
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
