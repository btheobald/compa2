#pragma once
#include <GLFW\glfw3.h>
#include "AntTweakBar.h"

// Mouse Callback
void cursorPosCallback(GLFWwindow* window, double cursorX, double cursorY);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

// Keyboard Callback
void keyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void keyboardCharCallback(GLFWwindow* window, unsigned int codepoint);

// Window
void windowResizeCallback(GLFWwindow* window, int width, int height);

// Callback Setup
void setCallbacks(GLFWwindow* window);