#include "handling.hpp"
using namespace std;

double vectX = 0, vectY = 0;
double scaleFactor = 1;
double responsiveness = 2;
double oldaX = 0, oldaY = 0;

// Custom Inputs
// Returns true if mouse button held.
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
    if(checking & (glfwGetTime() - startTime > 0.15)) {
      held = true;
    }
  }

  if((glfwGetMouseButton(window, button) == GLFW_RELEASE)){
    checking = false;
    held = false;
  }

  return held;
}

// Checks if held and translates world based on vector.
void moveCamera(GLFWwindow* window, double cursorX, double cursorY){
  static double prevX, prevY;
  //static double vectX, vectY;
  if(!TwEventMousePosGLFW(cursorX, cursorY)) {
    if(getMouseHeld(window, 0)) {
      // Get Change in Cursor
      vectX += prevX - cursorX;
      vectY += prevY - cursorY;
    }
  }
  // Update Previous Position
  prevX = cursorX;
  prevY = cursorY;
}

void zoomCamera(double change){
  //static double scaleFactor;

  scaleFactor += change/10;
  if(scaleFactor < 0.3) {
    scaleFactor = 0.3;
  }
  if(scaleFactor > 10) {
    scaleFactor = 10;
  }
}

void getCoord(double cX, double cY, double &aX, double &aY) {
  GLint viewport[4];
  GLdouble modelview[16];
  GLdouble projection[16];

  // Z is not important here
  GLdouble ignoreZ;

  glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
  glGetDoublev(GL_PROJECTION_MATRIX, projection);
  glGetIntegerv(GL_VIEWPORT, viewport);

  gluUnProject(cX, cY, 0, modelview, projection, viewport, &aX, &aY, &ignoreZ);
  // Apply zoom and scale to coordinates
  aX = ((aX-(-vectX*responsiveness))/pow(scaleFactor,2));
  aY = ((aY-(-vectY*responsiveness))/pow(scaleFactor,2));
}

void matrixCamera(GLFWwindow* window) {
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glLoadIdentity();

  double msX, msY, aX, aY;
  int wX, wY;
  glfwGetCursorPos(window, &msX, &msY);
  glfwGetWindowSize(window, &wX, &wY);
  getCoord(msX, msY, aX, aY);

  double zoomToX = aX - oldaX;
  double zoomToY = aY - oldaY;

  glTranslated(zoomToX, -zoomToY, 0);
  glScaled(pow(scaleFactor,2), pow(scaleFactor,2), 0);
  glTranslated(zoomToX, -zoomToY, 0);
  glTranslated((-vectX*responsiveness), (vectY*responsiveness), 0);
  glPushMatrix();

  cerr << zoomToX << " " << zoomToY << endl;
}

// Input
void cursorPosCallback(GLFWwindow* window, double cursorX, double cursorY) {
  if(!TwEventMousePosGLFW(cursorX, cursorY)) {
    moveCamera(window, cursorX, cursorY);
  }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  if(!TwEventMouseButtonGLFW(button, action)) {}
}

void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
  if(!TwEventMouseWheelGLFW(yoffset)) {
    zoomCamera(yoffset);
  }
}

void keyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if(!TwEventKeyGLFW(key, action)) {}
}

void keyboardCharCallback(GLFWwindow* window, unsigned int codepoint) {
  if(!TwEventCharGLFW(codepoint, GLFW_PRESS)) {}
}

// Window
void windowResizeCallback(GLFWwindow* window, int width, int height) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-width, width, -height, height, 1.0f, -1.0f);

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glLoadIdentity();

  double cX, cY;
  glfwGetCursorPos(window, &cX, &cY);

  glTranslated(-vectX*responsiveness+cX, vectY*responsiveness+cY, 0);
  glScaled(pow(scaleFactor,2), pow(scaleFactor,2), 0);

  TwWindowSize(width, height);

  glViewport(0, 0, width, height);

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
