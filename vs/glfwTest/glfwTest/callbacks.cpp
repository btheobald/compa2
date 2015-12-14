#include "callbacks.h"
#include <iostream>
using namespace std;

static void cursorPosCallback(GLFWwindow* window, double cursorX, double cursorY) {
  if(!TwEventMousePosGLFW(cursorX, cursorY)) {
    // Event has not been handled by ATB.
  }
}

void mouseButtonCallback(GLFWwindow * window, int button, int action, int mods) {
  if(!TwEventMouseButtonGLFW(button, action)) {
    // Event has not been handled by ATB.
  }
}

void mouseScrollCallback(GLFWwindow * window, double xoffset, double yoffset) {
  if(!TwEventMouseWheelGLFW(yoffset)) {
    // Event has not been handled by ATB.
  }
}

void keyboardKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods) {
  if(!TwEventKeyGLFW(key, action)) {
    cout << key << " : " << action << endl;
  }
}

void keyboardCharCallback(GLFWwindow * window, unsigned int codepoint) {
  if(!TwEventCharGLFW(codepoint, GLFW_PRESS)) {
    cout << codepoint << endl;
  }
}

void setCallbacks(GLFWwindow* window) {
  // Send GLFW Events to AntTweakBar
  glfwSetCursorPosCallback(window, cursorPosCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);
  glfwSetScrollCallback(window, mouseScrollCallback);
  glfwSetKeyCallback(window, keyboardKeyCallback);
  glfwSetCharCallback(window, keyboardCharCallback);
}