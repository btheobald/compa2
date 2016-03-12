#pragma once
#include <GLFW/glfw3.h>   // GLFW
#include "AntTweakBar.h"  // AntTweakBar
#include <iostream>
#include <cmath>
#include <GL/glu.h>
#include "render.hpp"
#include "body.hpp"
#include "scenario.hpp"

// Applys camera transform and scale
void applyCamera(GLFWwindow* window);

// Callback setup
void setCallbacks(GLFWwindow* window);

// Update functions
void updateUI(render* renderAP);
void updateBody(render* renderAP);

void setupGUI(GLFWwindow* window, render* renderAP);
