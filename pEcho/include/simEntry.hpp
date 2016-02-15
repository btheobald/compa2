#pragma once
#include "sim_obj.hpp"
#include "body.hpp"
#include "sharedStage.hpp"
#include "com.hpp"

#include <condition_variable>
#include <mutex>
#include <GLFW/glfw3.h>

// Initial Simulation Thread Call
void simInit(sharedStage* sharedDataAccess);
