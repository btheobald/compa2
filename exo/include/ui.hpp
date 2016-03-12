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
// Custom inputs
// Returns true if mouse button held.
//bool getMouseHeld(GLFWwindow* window, int button);
// Checks if held and translates world based on vector.
//void moveCamera(GLFWwindow* window, double cursorX, double cursorY);
//void zoomCamera(double change);
// Transforms window system coordinates to world space
//void getCoord(GLFWwindow* window, double &aX, double &aY);

// Mouse callbacks
//void cursorPosCallback(GLFWwindow* window, double cursorX, double cursorY);
//void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
//void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

// Keyboard callbacks
//void keyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
//void keyboardCharCallback(GLFWwindow* window, unsigned int codepoint);

// Window
//void windowResizeCallback(GLFWwindow* window, int width, int height);

// Callback setup
void setCallbacks(GLFWwindow* window);

// Update functions
void updateUI(render* renderAP);
void updateBody(render* renderAP);

// TweakBar button callbacks
//void TW_CALL deleteBodyButton(void *cData);
//void TW_CALL deleteAllBodiesButton(void *cData);
//void TW_CALL newBodyButton(void *cData);
//void TW_CALL newSuperStructureButton(void *cData);

// Sim and System gui Setup, Will be called once at start.
//void setupSimGUI(render* renderAP);
//void setupBodyGUI(render* renderAP);
//void setupSuperStructGUI(render* renderAP);
void setupGUI(GLFWwindow* window, render* renderAP);
