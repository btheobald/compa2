#include "ui.hpp"
using namespace std;

// GUI Pointers
TwBar* simGUI;
TwBar* bodyGUI;
// Used by GUI
static render* g_renderAP;
// Render Data Access Pointers
control ifControl;
std::vector<body*> ifBodies;
// Active Body
int activeBody = 1;

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
      int id = g_renderAP->checkCoord(aX, aY, (1/scaleFactor)*10);
      if(id != -1) {
        activeBody = id;
      }
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

void setupGUI(GLFWwindow* window, render* renderAP) {
  // Get GLFW window size
  int wX, wY;
  glfwGetWindowSize(window, &wX, &wY);

  // Set global render access pointer
  g_renderAP = renderAP;

  // Init AntTweakBar
  TwInit(TW_OPENGL, NULL);
  TwWindowSize(wX, wY);

  ifControl = g_renderAP->getControl();
  ifBodies = g_renderAP->getBodies();

  simGUI = TwNewBar("Simulation");
  bodyGUI = TwNewBar("Body");

  setupSimGUI();
  setupBodyGUI();

  // Set Globals
  TwDefine(" GLOBAL contained=true ");
  TwDefine(" GLOBAL fontresizable=false ");
  TwDefine(" GLOBAL fontstyle=default ");
  TwDefine(" GLOBAL buttonalign=center");
}

void setupSimGUI() {
  // Color
  TwDefine(" 'Simulation' color='255 255 255' alpha=150 text=dark");

  // Size
  TwDefine(" 'Simulation' size='300 180'");
  TwDefine(" 'Simulation' position='0 0'");
  TwDefine(" 'Simulation' resizable=false ");
  TwDefine(" 'Simulation' valueswidth=100 ");
  TwDefine(" 'Simulation' movable=false");
  TwDefine(" 'Simulation' refresh=0.01");

  // Control
  TwAddVarRW(simGUI, "ugcvar", TW_TYPE_DOUBLE,  &ifControl.UGC,        " min=1E-12  max=10   step=0.01  precision=7   label='Gravitational Constant'  group=Control ");
  TwAddVarRW(simGUI, "idtvar", TW_TYPE_DOUBLE,  &ifControl.IDT,        " max=-1E9   max=1E15  step=0.01  precision=7   label='Itteration Delta Time'   group=Control ");
  TwAddVarRW(simGUI, "collid", TW_TYPE_BOOLCPP, &ifControl.collide,"true=On      false=Off                       label='Simulate Collisions'     group=Control ");
  // Runtime
  TwAddVarRW(simGUI, "paused", TW_TYPE_BOOLCPP, &ifControl.paused,     " true=Paused  false=Running                   label='Run/Pause'               group=Runtime ");
  TwAddVarRW(simGUI, "ipfvar", TW_TYPE_INT32,   &ifControl.IPF,        " min=1      max=10000  step=1                 label='Itterations Per Frame'   group=Runtime ");
  // Statistics
//  TwAddVarRO(simGUI, "numbod", TW_TYPE_INT32,   &bodies.size(),  "                                              label='Number of Bodies'        group=Statistics ");
}

void setupBodyGUI() {
  // Color
  TwDefine(" 'Body' color='255 255 255' alpha=150 text=dark");

  // Size
  TwDefine(" 'Body' size='300 330'");
  TwDefine(" 'Body' position='0 182'");
  TwDefine(" 'Body' resizable=false ");
  TwDefine(" 'Body' valueswidth=100 ");
  TwDefine(" 'Body' movable=false");
  TwDefine(" 'Body' refresh=0.01");

  TwAddVarRO(bodyGUI, "bodyid", TW_TYPE_INT32, &activeBody,        "                                              label='Selected Body ID' ");
  TwAddVarRW(bodyGUI, "bdmass", TW_TYPE_DOUBLE,  &ifBodies[activeBody]->m,    " min=1E-3  max=1E40 step=1      precision=7   label='Mass'                    group=Properties ");
  TwAddVarRW(bodyGUI, "bdradi", TW_TYPE_DOUBLE,  &ifBodies[activeBody]->r,  " min=1E-3  max=1E20 step=1      precision=7   label='Radius'                  group=Properties ");
  TwAddVarRW(bodyGUI, "bdfixd", TW_TYPE_BOOLCPP, &ifBodies[activeBody]->fixed,   " true=Yes      false=No                       label='Fixed'                   group=Properties ");
//  TwAddVarRW(bodyGUI, "bdcolr", TW_TYPE_COLOR3F, &bodies[cB]->,   " coloralpha=false                             label='Colour'                  group=Properties ");

  TwAddVarRW(bodyGUI, "bdposx", TW_TYPE_DOUBLE, &ifBodies[activeBody]->pX,     " min=-1E15 max=1E40 step=1 precision=7   label='X'                       group=Position ");
  TwAddVarRW(bodyGUI, "bdposy", TW_TYPE_DOUBLE, &ifBodies[activeBody]->pY,     " min=-1E15 max=1E15 step=1 precision=7   label='Y'                       group=Position ");
  TwAddVarRW(bodyGUI, "bdvelx", TW_TYPE_DOUBLE, &ifBodies[activeBody]->vX,     " min=-3E8  max=3E8  step=1 precision=7   label='X'                       group=Velocity ");
  TwAddVarRW(bodyGUI, "bdvely", TW_TYPE_DOUBLE, &ifBodies[activeBody]->vY,     " min=-3E8  max=3E8  step=1 precision=7   label='Y'                       group=Velocity ");
  TwAddVarRO(bodyGUI, "bdaccx", TW_TYPE_DOUBLE, &ifBodies[activeBody]->aX, "                           precision=7   label='X'                       group=Acceleration ");
  TwAddVarRO(bodyGUI, "bdaccy", TW_TYPE_DOUBLE, &ifBodies[activeBody]->aY, "                           precision=7   label='Y'                       group=Acceleration ");

  //TwAddButton(bodyGUI,"delbody", deleteBodyButton, this, " label='Delete Body' ");
}

void TW_CALL deleteBodyButton(void *cData) {

}

void TW_CALL newBodyButton(void *cData) {

}

void TW_CALL newSuperStructureButton(void *cData) {

}
