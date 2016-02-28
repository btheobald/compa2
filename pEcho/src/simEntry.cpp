// Header Include
#include "simEntry.hpp"

void simInit(sharedStage* sharedDataAccess) {
  // Sim Wait Control Mutex
  std::mutex simWaitMTX;
  // Init Scenario
  sim_obj simMain;

  // Get Body Data from shared
  simMain.updateLocalStore(sharedDataAccess);

  // Check Exit Request
  while (!sharedDataAccess->getStatus(1)) {
    // Update Control
    simMain.updateLocalControl(sharedDataAccess);

    if(sharedDataAccess->getStatus(0)) { // Update Local from Render
      if(!sharedDataAccess->newSScenarioCheck()) {
        simMain.updateLocalStore(sharedDataAccess);
      }
    } else { // Update Shared from Sim
      // Check for pause or exit request
      if(!(sharedDataAccess->getStatus(0) | sharedDataAccess->getStatus(1))) {
        for(int icnt = 0; icnt < simMain.getIPF(); icnt++) {
          simMain.itteration();
          // Drop out if exit request
          if(sharedDataAccess->getStatus(1)) break;
        }
      }
      simMain.updateSharedArea(sharedDataAccess);
    }

    // Wait for data change
    std::unique_lock<std::mutex> uniqueSimWaitMTX(simWaitMTX);
    sharedDataAccess->simWait.wait(uniqueSimWaitMTX);

  }
  // Sim Now Exits
}
