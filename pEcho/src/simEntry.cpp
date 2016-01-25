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
  // Init Scenario
  sim_obj simMain;

  // Get Body Data from shared
  simMain.populateBodyStore(sharedDataAccess -> returnBodyStore_R());

  while (!(sharedDataAccess -> getStatus(1))) {
    // Update Simulation Constants
    simMain.setIDT(sharedDataAccess -> getSimIDT());
    simMain.setUGC(sharedDataAccess -> getSimUGC());

    // TODO: Check for interface updates
    // TODO: Check if new sim frame required
    // TODO: Mass Update Body Store

    simMain.itteration();
  }

  cerr << "Sim Exit" << endl;
}
