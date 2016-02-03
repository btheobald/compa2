#include "callbacks.h"
#include <iostream>
using namespace std;

// Input
void cursorPosCallback(GLFWwindow* window, double cursorX, double cursorY) {
  if(!TwEventMousePosGLFW(cursorX, cursorY)) {}
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  if(!TwEventMouseButtonGLFW(button, action)) {}
}

void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
  if(!TwEventMouseWheelGLFW(yoffset)) {}
}

void keyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if(!TwEventKeyGLFW(key, action)) {}
}

void keyboardCharCallback(GLFWwindow* window, unsigned int codepoint) {
  if(!TwEventCharGLFW(codepoint, GLFW_PRESS)) {}
}

// Window
void windowResizeCallback(GLFWwindow* window, int width, int height) {

}

void setCallbacks(GLFWwindow* window) {
  // Send GLFW Input Events to AntTweakBar
  glfwSetCursorPosCallback(window, cursorPosCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);
  glfwSetScrollCallback(window, mouseScrollCallback);
  glfwSetKeyCallback(window, keyboardKeyCallback);
  glfwSetCharCallback(window, keyboardCharCallback);

  // Resize Window
  glfwSetWindowSizeCallback(window, windowResizeCallback);
}