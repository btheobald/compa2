// Header Include
#include "simEntry.hpp"

void simInit(sharedStage* sharedDataAccess) {
  // Sim Wait Control Mutex
  std::mutex simWaitMTX;
  // Init Scenario and Access Pointer
  sim_obj simMain;

  // Get Body Data from shared
  simMain.updateLocalStore(sharedDataAccess);

  bool shouldPull = false;

  // Check Exit Request
  while (!sharedDataAccess->getStatus(1)) {
    std::cerr << shouldPull << std::endl;

    // Get new Render Data if Paused
    simMain.updateLocalStore(sharedDataAccess);
    std::cerr << "Update Taken" << std::endl;

    // If not paused
    if(!sharedDataAccess->getStatus(0)) {
      // Wait for old data to be taken.
      if(sharedDataAccess->newSScenarioCheck()) {
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
