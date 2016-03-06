#include "scenario.hpp"
#include <mutex>

class shared: public scenario {
private:
  mutex bodyLock; // Lock for shared body store
  mutex controlLock; // Lock for shared control store

public:
  // Local store in shared (Polymorphic),
  void updateLocalBodies(vector<body*> p_bodies);
  void updateLocalControl(control p_control);

  // Shared area cannot update itself
  void updateSharedBodies() = 0;
  void updateSharedControl() = 0;
}
