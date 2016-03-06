#pragma once

#include "body.hpp"
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
  std::vector<body*> bodies; // Vector containing pointers to body objects
  control lControl; // structure containing control variables

public:
  scenario();
  ~scenario();

  // Storage vector functions
  void addBody(body* p_nb); // Add body pointer to vector
  void delBody(int p_bdID); // Free body pointer from vector
  void deleteAllBodies();   // Free all bodies in vector

  // Data management
  // Update local body storage
  virtual inline void updateLocalBodies(std::vector<body*> p_bodies) { bodies = p_bodies; };
  // Update local control storage
  virtual inline void updateLocalControl(control p_control) { lControl = p_control; };
  // Get local body storage - Needed by interface
  virtual inline std::vector<body*> getLocalBodies(void) { return bodies; };
  // Get local control storage - Needed by interface
  virtual inline control getLocalControl(void) { return lControl; };
};
