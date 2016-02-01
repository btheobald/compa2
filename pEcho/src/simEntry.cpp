/*
*| Project Echo Simulation
*| Revision: 0.01
*| Author: Byron Theobald
*/

#include "simEntry.hpp"
using namespace std;

void simInit(sharedStage* sharedDataAccess) {
  // Sim Wait Control Mutex
  mutex simWaitMTX;
  // Init Scenario and Access Pointer
  sim_obj simMain;
  sim_obj* simMainAccess = &simMain;

  // Get Body Data from shared
  simMain.populateBodyStore(sharedDataAccess -> returnBodyStore_R());

  while (!(sharedDataAccess -> getStatus(1))) {
    // Update Simulation Control
    simMainAccess -> setUGC(sharedDataAccess -> getUGC());
    simMainAccess -> setIDT(sharedDataAccess -> getIDT());
    simMainAccess -> setIPF(sharedDataAccess -> getIPF());

    // Check If Paused
    if(!(sharedDataAccess -> getStatus(0))) {
      for(int icnt = simMainAccess -> getIPF(); icnt--;) {
        simMain.itteration();
      }
    }

    if(sharedDataAccess -> newSScenarioCheck()) {
      unique_lock<mutex> uniqueSimWaitMTX(simWaitMTX); // Unique Lock ensures that mutex will be unlocked on destruction.
      sharedDataAccess -> simWait.wait(uniqueSimWaitMTX); // Wait for data to be taken.
    }
    sharedDataAccess -> populateBodyStore_S(simMainAccess -> returnBodyStore());
  }

  cerr << "Sim Exit" << endl;
}
