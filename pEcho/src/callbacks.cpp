#include "callbacks.hpp"
using namespace std;

// Custom Inputs
// Returns true if mouse button held
bool getMouseHeld(GLFWwindow* window, int button){
  static bool checking;
  static bool held;
  static double startTime;

  if((glfwGetMouseButton(window, button) == GLFW_PRESS)) {
    //std::cerr << "Mouse Clicked : " << glfwGetTime() << std::endl;
    if(!checking) {
      startTime = glfwGetTime();
    }
    checking = true;
    if(checking & (glfwGetTime() - startTime > 0.4)) {
      held = true;
    }
  }

  if((glfwGetMouseButton(window, button) == GLFW_RELEASE)){
    checking = false;
    held = false;
  }
}

void handleInputs(GLFWwindow* window) {
  // Manual
  getMouseHeld(window, 0);

  // GLFW Handled
  glfwPollEvents();
}

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
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glLoadIdentity();

  glViewport(width, height, -width, -height);

  glPushMatrix();
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
