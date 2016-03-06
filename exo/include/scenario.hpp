#include <vector>

// Control structure
typedef struct {
  // Simulation control
  double UGC; // Gravitational constant
  double IDT; // Itteration Δ time
  double IPF; // Itterations per frame
  bool collide; // Simulate collisions
  bool paused;  // Simulation paused

  // Exit Management
  bool exit;
  bool exitAck;
} control;

class scenario {
protected:
  vector<body*> bodies; // Vector containing pointers to body objects
  control lControl; // Object containing control variables

public:
  scenario();
  ~scenario();

  // Storage vector functions
  void addBody(body* p_nb); // Add body pointer to vector
  void delBody(int p_bdID); // Free body pointer from vector
  void deleteAllBodies();   // Free all bodies in vector

  // Data management
  // Update local body storage
  virtual inline void updateLocalBodies(vector<body*> p_bodies) { bodies = p_bodies; };
  // Update local control storage
  virtual inline void updateLocalControl(control p_control) { lControl = p_control; };
  // Commit bodies to shared
  virtual inline void updateSharedBodies(shared* stage) { stage->updateLocalBodies(bodies); };
  // Commit control to shared
  virtual inline void updateSharedControl(shared* stage) { stage->updateLocalControl(lControl); };
}
