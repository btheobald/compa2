//#include <iostream>
#include "scenario.hpp"
#include "render.hpp"
#include "simulation.hpp"
#include <thread>

// Sim thread startup function
void startup(shared* sharedAP);

int main() {
  // Create access pointers
  render* renderAP = new render;
  shared* sharedAP = new shared;

  renderAP->addBody(new body(1, 0, 0, 0, true));
  renderAP->addBody(new body(1, 0, 10, 0, 0, 3.16));

  // Create simulation thread
  std::thread simThread(startup, sharedAP);


  // Program Exit
  simThread.join();
  delete renderAP;
  delete sharedAP;

  return 0;
}

void startup(shared* sharedAP) {
  simulation* simAP = new simulation;

  delete simAP;
}
