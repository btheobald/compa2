#pragma once
// Standard Library Includes
#include <condition_variable>
#include <mutex>
#include <thread>
// Custom Headers
#include "sim_obj.hpp"
#include "body.hpp"
#include "sharedStage.hpp"
#include "com.hpp"

// Initial Simulation Thread Call
void workerThread(sim_obj* simAccess, int threadsUsed, int threadID, int stage);
void simInit(sharedStage* sharedDataAccess);
