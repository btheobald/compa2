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
  // Init Scenario and Access Pointer
  sim_obj simMain;
  sim_obj* simMainAccess = &simMain;

  // Get Body Data from shared
  simMain.populateBodyStore(sharedDataAccess -> returnBodyStore_R());
  cout << "Get New : Sim" << endl;

  while (!(sharedDataAccess -> getStatus(1))) {
    // Update Simulation Control
    simMainAccess -> setUGC(sharedDataAccess -> getUGC());
    simMainAccess -> setIDT(sharedDataAccess -> getIDT());
    simMainAccess -> setIPF(sharedDataAccess -> getIPF());

    // Check If Paused
    if(!(sharedDataAccess -> getStatus(0))) {
      for(int icnt = 0; icnt < (simMainAccess -> getIPF()); icnt++) {
        simMain.itteration();
      }
    }

    sharedDataAccess -> populateBodyStore_S(simMainAccess -> returnBodyStore());
    cout << "Push New : Sim" << endl;
  }

  cerr << "Sim Exit" << endl;
}
