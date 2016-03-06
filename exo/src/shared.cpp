#include "shared.hpp"

void shared::updateLocalBodies(std::vector<body*> p_bodies) {
  // Must create a copy of objects at pointers, not just copy pointers
  // Lock access to body store
  std::lock_guard<std::mutex> lock(bodyLock);
  bodies.reserve(p_bodies.size()); // Reserve space to create copy

  for(unsigned int i = 0; i < p_bodies.size(); i++) {
    addBody(new body(p_bodies[i])); // Adds to 'bodies' (Scenario Local)
  }
}

void shared::updateLocalControl(control p_control) {
  // Lock access to control store
  std::lock_guard<std::mutex> lock(controlLock);
  lControl = p_control;
}

std::vector<body*> shared::getLocalBodies(void) {
  // Lock access to body store
  std::lock_guard<std::mutex> lock(bodyLock);
  std::vector<body*> r_bodies;

  r_bodies.reserve(bodies.size()); // Reserve space to create copy

  for(unsigned int i = 0; i < bodies.size(); i++) {
    r_bodies.push_back(new body(bodies[i])); // Adds to 'bodies' (Scenario Local)
  }
  return r_bodies;
}

control shared::getLocalControl(void) {
  // Lock access to body store
  std::lock_guard<std::mutex> lock(controlLock);
  return lControl;
}
