//#include <iostream>
#include "scenario.hpp"
#include "simulation.hpp"
#include <thread>

int main() {
  // Create access pointers
  simulation* simAP = new simulation;

  // Add bodies
  simAP->addBody(new body(1, 0, 0, 0, true));
  simAP->addBody(new body(1, 0, 10, 0, 0, 0.316));
  simAP->addBody(new body(1, 0, 1, 0, 0, 1));

  control local;
  local.UGC = 1;
  local.IDT = 0.1;

  simAP->updateLocalControl(local);

  for(int i = 0; i < 2000; i++) {
    simAP->itteration();
  }

  simAP->deleteAllBodies();
  delete(simAP);

  return 0;
}
