#pragma once
#include "sim_obj.hpp"
#include "body.hpp"
#include "sharedStage.hpp"

#include <iostream>
#include <vector>
#include <condition_variable>
#include <mutex>

mutex simWaitMTX;

// Initial Simulation Thread Call
void simInit(sharedStage* sharedDataAccess);
