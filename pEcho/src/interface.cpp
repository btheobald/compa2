#include "interface.hpp"

bool interface::getMouseHeld(GLFWwindow* window, int button){
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

void interface::updateMouseActual() {
  // Declare Temporary Matrix Storage
  GLint viewport[4];
  GLdouble modelview[16];
  GLdouble projection[16];
  GLdouble dZ; // Dud Z

  // Convert all Current Matrix
  glGetIntegerv(GL_VIEWPORT, viewport);
  glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
  glGetDoublev(GL_PROJECTION_MATRIX, projection);

  // Correct for Inverted Window System Coordinates
  double winXC = viewport[3] - winY;

  // Get Actual World Cordinates
  gluUnProject(winXC, winY, 0, modelview, projection, viewport, &actX, &actY, &dZ);
}

// Input
void interface::cursorPos(GLFWwindow* window) {
  if(!TwEventMousePosGLFW(winX, winY)) {
    if(getMouseHeld(window, 0)) {
      // Get Change in Cursor
      cameraPosX += cameraPosX - winX;
      cameraPosY += cameraPosY - winY;
    }
    // Update Previous Position
    prevWinX = winX;
    prevWinY = winY;
  }
}

void interface::mouseButton(GLFWwindow* window) {
/*  if(!TwEventMouseButtonGLFW(button, action)) {
    if((button == 1) & (action == GLFW_PRESS)) {// Get Cursor Position and Convert to World Coordinates
      //winX = cursorX;
      //winY = cursorY;
      updateMouseActual();
    }
  }*/
}

void interface::mouseScroll(GLFWwindow* window) {
/*  if(!TwEventMouseWheelGLFW(yoffset)) {
    scaleFact += yoffset/10;
    if(scaleFact < 0.01) {
      scaleFact = 0.01;
    }
    if(scaleFact > 10) {
      scaleFact = 10;
    }
  }*/
}

void interface::keyboardKey(GLFWwindow* window) {
  //if(!TwEventKeyGLFW(key, action)) {}
}

void interface::keyboardChar(GLFWwindow* window) {
  //if(!TwEventCharGLFW(codepoint, GLFW_PRESS)) {}
}

// Window
void interface::windowResize(GLFWwindow* window) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-resX, resX, -resY, resY, 1.0f, -1.0f);

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glLoadIdentity();

  TwWindowSize(resX, resY);
  glViewport(0, 0, resX, resY);

  glPushMatrix();
}

interface::interface(GLFWwindow* window) {
  scaleFact = 1;
  moveFact = 2;
  cameraPosX = 0;
  cameraPosY = 0;
}

interface::~interface() {

}

void interface::inputLoop(GLFWwindow* window) {
  glfwGetCursorPos(window, &winX, &winY);
  glfwGetWindowSize(window, &resX, &resY);

  cursorPos(window);

  performOperations();
}

void interface::performOperations() {
  // Get Identity ModelView Matrix
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glLoadIdentity();

  // Apply Scale and Transformation
  //glScaled(pow(scaleFact,2), pow(scaleFact,2), 1);
  glTranslated((cameraPosX*moveFact), (cameraPosY*moveFact), 0);
  glPushMatrix();
}
