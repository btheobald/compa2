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

    // Simulation Old Data Has Not Been Taken
    if(sharedDataAccess->newSScenarioCheck()) {
      // Unique Lock ensures that mutex will be unlocked on destruction.
      std::unique_lock<std::mutex> uniqueSimWaitMTX(simWaitMTX);
      // Wait for data to be taken.
      sharedDataAccess->simWait.wait(uniqueSimWaitMTX);
    }
    // Stage Data to Shared Area
    sharedDataAccess->populateBodyStore_S(simMain.returnBodyStore());

    // Update Simulation Control
    simMain.setUGC(sharedDataAccess->getUGC());
    simMain.setIDT(sharedDataAccess->getIDT());
    simMain.setIPF(sharedDataAccess->getIPF());

    // Check If Paused or Exit Request
    if(!(sharedDataAccess->getStatus(0) | sharedDataAccess->getStatus(1))) {
      for(int icnt = 0; icnt < simMain.getIPF(); icnt++) {
        simMain.preItteration();

        for(int threads = 0; threads < simMain.getThreadCount(); threads++) {
          simMain.itteration_vp(simMain.getRange(simMain.getThreadCount(), threads, false), simMain.getRange(simMain.getThreadCount(), threads, true));
        }

        for(int threads = 0; threads < simMain.getThreadCount(); threads++) {
          simMain.itteration_f(simMain.getRange(simMain.getThreadCount(), threads, false), simMain.getRange(simMain.getThreadCount(), threads, true));
        }

        for(int threads = 0; threads < simMain.getThreadCount(); threads++) {
          simMain.itteration_av(simMain.getRange(simMain.getThreadCount(), threads, false), simMain.getRange(simMain.getThreadCount(), threads, true));
        }
      }
    }
  }
  // Sim Now Exits
}
