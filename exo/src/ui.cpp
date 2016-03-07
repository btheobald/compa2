#include "ui.hpp"
using namespace std;

static render* renderAP;

double vectX = 0, vectY = 0;
double scaleFactor = 1;
double responsiveness = 2;
double oldaX = 0, oldaY = 0;

// Custom Inputs
// Returns true if mouse button held.
bool getMouseHeld(GLFWwindow* window, int button) {
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
      held = true;
  }

  if((glfwGetMouseButton(window, button) == GLFW_RELEASE)){
    checking = false;
    held = false;      //shouldCheck = true;
  }

  return held;
}

// Checks if held and translates world based on vector.
void moveCamera(GLFWwindow* window, double cursorX, double cursorY){
  static double prevX, prevY;
  if(!TwEventMousePosGLFW(cursorX, cursorY)) {
    if(getMouseHeld(window, 2)) {
      // Get Change in Cursor
      vectX += ((prevX - cursorX) * responsiveness) * (1/scaleFactor);//pow(1/scaleFactor,2);
      vectY += ((prevY - cursorY) * responsiveness) * (1/scaleFactor);//pow(1/scaleFactor,2);
    }
  }
  // Update Previous Position
  prevX = cursorX;
  prevY = cursorY;
}

void zoomCamera(double change){
  double changeFactor = scaleFactor/5;
  scaleFactor += change*changeFactor;
  if(scaleFactor < 1E-20) {
    scaleFactor = 1E-20;
  }
  if(scaleFactor > 1E3) {
    scaleFactor = 1E3;
  }
  //std::cerr << scaleFactor << std::endl;
}

// Transforms window system coordinates to world space
void getCoord(GLFWwindow* window, double &aX, double &aY) {
  double mX, mY; // Window system mouse
  glfwGetCursorPos(window, &mX, &mY);

  // Initialise local display matrix storage
  GLint viewport[4];
  GLdouble modelview[16];
  GLdouble projection[16];
  // Get current display matricies
  glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
  glGetDoublev(GL_PROJECTION_MATRIX, projection);
  glGetIntegerv(GL_VIEWPORT, viewport);

  // Flip window y
  mY = viewport[3] - mY;

  // Z is not important here, variable is required
  GLdouble ignoreZ;

  // Project mouse to world
  gluUnProject(mX, mY, 0, modelview, projection, viewport, &aX, &aY, &ignoreZ);
}

// Applys camera transform and scale
void applyCamera(GLFWwindow* window) {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glScaled(scaleFactor, scaleFactor, 1);

  glTranslated(-vectX, vectY, 0);

  glPushMatrix();
}

// Input
void cursorPosCallback(GLFWwindow* window, double cursorX, double cursorY) {
  if(!TwEventMousePosGLFW(cursorX, cursorY)) {
    moveCamera(window, cursorX, cursorY);
  }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  if(!TwEventMouseButtonGLFW(button, action)) {
    if((action == GLFW_PRESS) & (button == 0)) {
      double aX, aY;
      getCoord(window, aX, aY);
      std::cerr << renderAP->checkCoord(aX, aY, (1/scaleFactor)*10) << std::endl;
    }
  }
}
void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
  if(!TwEventMouseWheelGLFW(yoffset)) {
    zoomCamera(yoffset);
  }
}

// Window
void windowResizeCallback(GLFWwindow* window, int width, int height) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-width, width, -height, height, 1.0f, -1.0f);

  applyCamera(window);

  TwWindowSize(width, height);

  glViewport(0, 0, width, height);

  glPushMatrix();
}

void setCallbacks(GLFWwindow* window) {
  // Send GLFW Input Events to AntTweakBar
  glfwSetCursorPosCallback(window, cursorPosCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);
  glfwSetScrollCallback(window, mouseScrollCallback);

  // Resize Window
  glfwSetWindowSizeCallback(window, windowResizeCallback);
}

void setRenderPointer(render* p_renderAP) {
  renderAP = p_renderAP;
}
