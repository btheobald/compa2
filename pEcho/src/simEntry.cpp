/*
*| Project Echo Simulation
*| Revision: 0.01
*| Author: Byron Theobald
*/

#include <iostream>
#include <vector>
#include "simEntry.hpp"
using namespace std;

void simInit(sharedStage* sharedDataAccess) {
  sim_obj simMain;

  // Set Initial Simulation Constants
  simMain.setTimestep(0.01);
  simMain.setGravConst(0.1);

  vector<body> ifcBodyStore; // Simulation Interface Body Store (Scope)

  // TODO: Move these to header in Render Component.
  // Body Positions
  double b0Pos[2] = { 0.0, 0.0 };
  double b1Pos[2] = { 100.0, 0.0 };
  double b2Pos[2] = { 102.0, 0.0 };
  // Body Velocities
  double b0Vel[2] = { 0.0, 0.0 };
  double b1Vel[2] = { 0.0, 1.0 };
  double b2Vel[2] = { 0.0, 1.30 };

  // Create Local Bodies
  ifcBodyStore.push_back(body(1000, 0.1, b0Pos, b0Vel));
  ifcBodyStore.push_back(body(2, 0.1, b1Pos, b1Vel));
  ifcBodyStore.push_back(body(0.01, 0.01, b2Pos, b2Vel));
  // Pass Pointer - This relies on the sim initialising all bodies prior to loop.
  for(int c = 0; c < 3; c++)
    simMain.newBody(&ifcBodyStore[c]);

  //for (int i = 0; i < ITTERATIONS; i++) {
  while (!(sharedDataAccess -> getStatus(1))) {
    sharedDataAccess -> populateBodyStore_R(simMain.returnBodyStore());
    // TODO: Check for interface updates
    // TODO: Check if new sim frame required
    // TODO: Mass Update Body Store

    simMain.itteration();
    simMain.populateBodyStore(sharedDataAccess -> returnBodyStore_R());

    #ifdef OUTPUT
    simMain.outputStore(i);
    #endif
    //cerr << i << '\r';
  }
  #ifdef OUTPUT
  simMain.outputToTerm();
  #endif

  //sharedDataAccess -> setStatus(TRUE, 2);
  cerr << "Sim Exit" << endl;
}
