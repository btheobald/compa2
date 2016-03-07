#pragma once

#include "body.hpp"
#include <vector>

// Control structure
typedef struct control {
  // Simulation control
  double UGC = 0.1; // Gravitational constant
  double IDT = 0.1; // Itteration Δ time
  double IPF = 1; // Itterations per frame
  bool collide = false; // Simulate collisions
  bool paused = false;  // Simulation paused

  // Exit Management
  bool exit = false;
  bool exitAck = false;
} control;

class scenario {
protected:
  std::vector<body*> bodies; // Vector containing pointers to body objects
  control lControl; // structure containing control variables

public:
  scenario();
  virtual ~scenario();

  // Storage vector functions
  void addBody(body* p_nb); // Add body pointer to vector
  void delBody(int p_bdID); // Free body pointer from vector
  void deleteAllBodies();   // Free all bodies in vector

  // Data management
  // Update local body storage
  virtual inline void updateBodies(std::vector<body*> p_bodies) { deleteAllBodies(); bodies = p_bodies; };
  // Update local control storage
  virtual inline void updateControl(control p_control) { lControl = p_control; };
  // Get local body storage - Needed by interface and to update shared (Returns actual pointer vector)
  virtual inline std::vector<body*> getBodies(void) { return bodies; };
  // Get local control storage - Needed by interface and to update shared
  virtual inline control getControl(void) { return lControl; };

  inline bool getPaused(void) { return lControl.paused; };
  inline bool getExit(void) { return lControl.exit; };
};
