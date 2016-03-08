#pragma once
#include <GLFW/glfw3.h>   // GLFW
#include <iostream>
#include <cmath>
#include <GL/glu.h>
#include "AntTweakBar.h"
#include "render.hpp"
#include "body.hpp"
#include "scenario.hpp"
#include <vector>

// Custom Inputs
bool getMouseHeld(GLFWwindow* window, int button);
void moveCamera(GLFWwindow* window, double cursorX, double cursorY);
void zoomCamera(double change);
void applyCamera(GLFWwindow* window);
void getCoord(GLFWwindow* window, double &aX, double &aY);

// Mouse Callback
void cursorPosCallback(GLFWwindow* window, double cursorX, double cursorY);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

// Window
void windowResizeCallback(GLFWwindow* window, int width, int height);

// Callback Setup
void setCallbacks(GLFWwindow* window);

void updateUI(render* renderAP, int abID);

// Sim and System gui Setup, Will be called once at start.
void setupGUI(GLFWwindow* window, render* renderAP);
void setupSimGUI(render* renderAP);
void setupBodyGUI(render* renderAP);

// Class External Callbacks
void TW_CALL saveFileButton();
void TW_CALL loadFileButton();

void TW_CALL deleteBodyButton(void *cData);
void TW_CALL newBodyButton(void *cData);
