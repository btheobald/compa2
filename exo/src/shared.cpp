#include "shared.hpp"
#include <iostream>

void shared::updateBodies(std::vector<body*> p_bodies) {
  // Must create a copy of objects at pointers, not just copy pointers
  // Lock access to body store
  std::lock_guard<std::mutex> lock(bodyLock);
  deleteAllBodies(); // Flush current body storage allocation
  bodies.reserve(p_bodies.size()); // Reserve space to create copy

  for(unsigned int i = 0; i < p_bodies.size(); i++) {
    addBody(new body(p_bodies[i])); // Adds to 'bodies' (Scenario Local)
  }
}

void shared::updateControl(control p_control) {
  // Lock access to control store
  std::lock_guard<std::mutex> lock(controlLock);
  lControl = p_control;
}

std::vector<body*> shared::getBodies(void) {
  // Lock access to body store
  std::lock_guard<std::mutex> lock(bodyLock);
  std::vector<body*> r_bodies;

  r_bodies.reserve(bodies.size()); // Reserve space to create copy

  for(unsigned int i = 0; i < bodies.size(); i++) {
    r_bodies.push_back(new body(bodies[i])); // Adds to 'bodies' (Scenario Local)
  }

  return r_bodies;
}

control shared::getControl(void) {
  // Lock access to body store
  std::lock_guard<std::mutex> lock(controlLock);
  return lControl;
}
