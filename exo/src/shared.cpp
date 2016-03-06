#include "shared.hpp"

void shared::updateLocalBodies(std::vector<body*> p_bodies) {
  // Lock access to body store
  std::lock_guard<std::mutex> lock(bodyLock);
  bodies = p_bodies;
}

void shared::updateLocalControl(control p_control) {
  // Lock access to control store
  std::lock_guard<std::mutex> lock(controlLock);
  lControl = p_control;
}

std::vector<body*> shared::getLocalBodies(void) {
  // Lock access to body store
  std::lock_guard<std::mutex> lock(bodyLock);
  return bodies;
}

control shared::getLocalControl(void) {
  // Lock access to body store
  std::lock_guard<std::mutex> lock(controlLock);
  return lControl;
}
