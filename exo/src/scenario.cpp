#include "scenario.hpp"
#include <iostream>
scenario::scenario() {
  lControl.UGC = 0.1;
  lControl.IDT = 1;
  lControl.IPF = 1;
  lControl.collide = false;
  lControl.paused = false;
  lControl.exit = false;
}

scenario::~scenario() {
  deleteAllBodies(); // Cleanup all bodies in local storage
}

void scenario::addBody(body* p_nb) {
  bodies.push_back(p_nb); // Add pointer to dynamic array
}

void scenario::delBody(int p_bdID) {
  delete(bodies[p_bdID]); // Free memory associated with pointer
  bodies.erase(bodies.begin()+p_bdID); // Erase pointer from vector
}

void scenario::deleteAllBodies() {
  for(unsigned int i = 0; i < bodies.size(); i++) {
    delete(bodies[i]); // Free all memory in vector pointers
  }
  bodies.clear(); // Reset vector
}

void scenario::updateBody(body* p_nb, int bodyID) {
  *bodies[bodyID] = *p_nb;
}

void scenario::updateBodies(std::vector<body*> p_bodies) {
  deleteAllBodies();
  bodies = p_bodies;
}

void scenario::updateControl(control p_control) {
  lControl = p_control;
}

std::vector<body*> scenario::getBodies(void) {
  return bodies;
}

control scenario::getControl(void) {
  return lControl;
}
