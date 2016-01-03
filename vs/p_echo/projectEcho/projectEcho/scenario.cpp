#include "scenario.h"



scenario::scenario() {
}


scenario::~scenario() {
}


int scenario::newBody(double p_Mass, double p_Radius, double p_Position[2], double p_Velocity[2]) {
  bodyStore.push_back(body(p_Mass, p_Radius, p_Position, p_Velocity));
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