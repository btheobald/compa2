#include "scenario.h"



scenario::scenario() {
}


scenario::~scenario() {
}


int scenario::newBody(body tempBody) {
  bodyStore.push_back(tempBody);
  bodyStore.front().setTimestep(timestep);
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