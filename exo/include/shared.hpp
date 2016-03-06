#pragma once

#include "scenario.hpp"
#include <mutex>

class shared: public scenario {
private:
  std::mutex bodyLock; // Lock for shared body store
  std::mutex controlLock; // Lock for shared control store

public:
  // Local store in shared (Polymorphic), add a mutex lock to access
  void updateBodies(std::vector<body*> p_bodies) override;
  void updateControl(control p_control) override;
  std::vector<body*> getBodies(void) override;
  control getControl(void) override;
};
