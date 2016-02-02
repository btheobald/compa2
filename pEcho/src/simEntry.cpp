// Header Include
#include "simEntry.hpp"

void simInit(sharedStage* sharedDataAccess) {
  // Sim Wait Control Mutex
  std::mutex simWaitMTX;
  // Init Scenario and Access Pointer
  sim_obj simMain;

  // Get Body Data from shared
  simMain.populateBodyStore(sharedDataAccess->returnBodyStore_R());

  // Check Exit Request
  while (!(sharedDataAccess->getStatus(1))) {
    // Stage Data to Shared Area
    // Simulation will wait if faster than Render
    if(sharedDataAccess->newSScenarioCheck()) {
      std::unique_lock<std::mutex> uniqueSimWaitMTX(simWaitMTX); // Unique Lock ensures that mutex will be unlocked on destruction.
      sharedDataAccess->simWait.wait(uniqueSimWaitMTX); // Wait for data to be taken.
    }
    sharedDataAccess->populateBodyStore_S(simMain.returnBodyStore());

    // Update Simulation Control
    simMain.setUGC(sharedDataAccess->getUGC());
    simMain.setIDT(sharedDataAccess->getIDT());
    simMain.setIPF(sharedDataAccess->getIPF());

    // Check If Paused or Exit Request
    if(!(sharedDataAccess->getStatus(0) | sharedDataAccess->getStatus(1))) {
      for(int icnt = 0; icnt < simMain.getIPF(); icnt++) {
        simMain.itteration();
      }
    }
  }
  // Sim Now Exits
}
