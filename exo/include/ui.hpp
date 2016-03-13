#pragma once

// External library includes
#include <GLFW/glfw3.h>   // GLFW
// Custom header includes
#include "render.hpp"
#include "body.hpp"
#include "scenario.hpp"

// Applys camera transform and scale
void applyCamera(void);

// Callback setup
void setCallbacks(GLFWwindow* window);

// Update functions
void updateUI(render* renderAP);
void updateBody(render* renderAP);

// Setup GUI Windows
void setupGUI(GLFWwindow* window, render* renderAP);
