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
    // Get new Render Data if Paused
    if(!sharedDataAccess->getStatus(0)) {
      simMain.updateLocalStore(sharedDataAccess);
      std::cerr << "Update Taken" << std::endl;
    }

    if(!sharedDataAccess->getStatus(0)) {
      // Wait for old data to be taken.
      if(sharedDataAccess->newSScenarioCheck() & !sharedDataAccess->getStatus(0)) {
        std::unique_lock<std::mutex> uniqueSimWaitMTX(simWaitMTX);
        sharedDataAccess->simWait.wait(uniqueSimWaitMTX);
      }

      // Stage Data to Shared Area
      simMain.updateSharedArea(sharedDataAccess);
      simMain.updateLocalControl(sharedDataAccess);
    }

    // Check If Paused or Exit Request
    if(!(sharedDataAccess->getStatus(0) | sharedDataAccess->getStatus(1))) {
      for(int icnt = 0; icnt < simMain.getIPF(); icnt++) {
        simMain.itteration();
      }
    }
    //std::cerr << glfwGetTime()-timer << std::endl;
  }
  // Sim Now Exits
}
