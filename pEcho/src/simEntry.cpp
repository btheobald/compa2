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

        std::thread threadStore[16]; // Hard Limit of 16 Threads

        int threadUsed = simMain.getThreadCount();

        for(int currentStage = 0; currentStage < 3; currentStage++) {
          for(int threadCounter = 0; threadCounter < threadUsed; threadCounter++) {
            threadStore[threadCounter] = std::thread(workerThread, &simMain, threadUsed, threadCounter, currentStage);
            //std::cerr << "Worker " << threadCounter << " Dispatched To Stage " << currentStage << std::endl;
          }
          for(int threadCounter = 0; threadCounter < threadUsed; threadCounter++) {
            threadStore[threadCounter].join();
            //std::cerr << "Worker " << threadCounter << " Joined." << std::endl;
          }
        }
      }
    }
  }
  // Sim Now Exits
}

void workerThread(sim_obj* simAccess, int threadsUsed, int threadID, int stage) {
  int upperRange = simAccess->getRange(threadsUsed, threadID, true);
  int lowerRange = simAccess->getRange(threadsUsed, threadID, false);

  switch(stage) {
    case 0: {
      simAccess->itteration_vp(lowerRange, upperRange);
      break;
    }
    case 1: {
      simAccess->itteration_f(lowerRange, upperRange);
      break;
    }
    case 2: {
      simAccess->itteration_av(lowerRange, upperRange);
      break;
    }
  }
}
