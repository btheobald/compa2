#pragma once
#include <GLFW/glfw3.h>   // GLFW
#include <iostream>
#include <cmath>
#include <GL/glu.h>
#include "AntTweakBar.h"
#include "render.hpp"

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
void setRenderPointer(render* p_renderAP);
