#include "scenario.h"



scenario::scenario() {
}


scenario::~scenario() {
}


int scenario::newBody(body *tempptr) {
  bodyStore.push_back(*tempptr);
  bodyStore[0].setTimestep(timestep);
  return 0;
}
int scenario::delBody(int index) {
  bodyStore.erase(bodyStore.begin() + index);
  return 0;
}
int scenario::delAllBodies(int index) {
  bodyStore.clear();
  return 0;
}

int scenario::setTimestep(double p_Timestep) {
  timestep = p_Timestep;
  return 0;
}

int scenario::setGravConst(double p_GravConst) {
  gravitationalConstant = p_GravConst;
  return 0;
}
