#include "ui.hpp"
using namespace std;

// Used by gui
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

gui::gui(int p_wXRes, int p_wYRes) {
  // Init AntTweakBar
  TwInit(TW_OPENGL, NULL);
  TwWindowSize(p_wXRes, p_wYRes);

  simGUI = TwNewBar("Simulation");
  bodyGUI = TwNewBar("Body");
  systemGUI = TwNewBar("System");

  setupSimGUI();
  setupBodyGUI(0);
  setupSystemGUI();

  // Set Globals
  TwDefine(" GLOBAL contained=true ");
  TwDefine(" GLOBAL fontresizable=false ");
  TwDefine(" GLOBAL fontstyle=default ");
  TwDefine(" GLOBAL buttonalign=center");
}

gui::~gui() {

}

void gui::setupSimGUI() {
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
  TwAddVarRW(simGUI, "ugcvar", TW_TYPE_DOUBLE,  &UGC_I,        " min=1E-12  max=10   step=0.01  precision=7   label='Gravitational Constant'  group=Control ");
  TwAddVarRW(simGUI, "idtvar", TW_TYPE_DOUBLE,  &IDT_I,        " max=-1E9   max=1E15  step=0.01  precision=7   label='Itteration Delta Time'   group=Control ");
  TwAddVarRW(simGUI, "collid", TW_TYPE_BOOLCPP, &doCollisions_I,"true=On      false=Off                       label='Simulate Collisions'     group=Control ");
  // Runtime
  TwAddVarRW(simGUI, "paused", TW_TYPE_BOOLCPP, &paused_I,     " true=Paused  false=Running                   label='Run/Pause'               group=Runtime ");
  TwAddVarRW(simGUI, "ipfvar", TW_TYPE_INT32,   &IPF_I,        " min=1      max=10000  step=1                 label='Itterations Per Frame'   group=Runtime ");
  // Statistics
  TwAddVarRO(simGUI, "numbod", TW_TYPE_INT32,   &numBodies_I,  "                                              label='Number of Bodies'        group=Statistics ");
}
void gui::setupBodyGUI(int p_abID) {
  // Color
  TwDefine(" 'Body' color='255 255 255' alpha=150 text=dark");

  // Size
  TwDefine(" 'Body' size='300 330'");
  TwDefine(" 'Body' position='0 182'");
  TwDefine(" 'Body' resizable=false ");
  TwDefine(" 'Body' valueswidth=100 ");
  TwDefine(" 'Body' movable=false");
  TwDefine(" 'Body' refresh=0.01");

  TwAddVarRO(bodyGUI, "bodyid", TW_TYPE_INT32, &abID_I,        "                                              label='Selected Body ID' ");
  TwAddVarRW(bodyGUI, "bdmass", TW_TYPE_DOUBLE,  &abMass_I,    " min=1E-3  max=1E40 step=1      precision=7   label='Mass'                    group=Properties ");
  TwAddVarRW(bodyGUI, "bdradi", TW_TYPE_DOUBLE,  &abRadius_I,  " min=1E-3  max=1E20 step=1      precision=7   label='Radius'                  group=Properties ");
  TwAddVarRW(bodyGUI, "bdfixd", TW_TYPE_BOOLCPP, &abFixed_I,   " true=Yes      false=No                       label='Fixed'                   group=Properties ");
  TwAddVarRW(bodyGUI, "bdcolr", TW_TYPE_COLOR3F, &abColor_I,   " coloralpha=false                             label='Colour'                  group=Properties ");

  TwAddVarRW(bodyGUI, "bdposx", TW_TYPE_DOUBLE, &abPositionX_I,     " min=-1E15 max=1E40 step=1 precision=7   label='X'                       group=Position ");
  TwAddVarRW(bodyGUI, "bdposy", TW_TYPE_DOUBLE, &abPositionY_I,     " min=-1E15 max=1E15 step=1 precision=7   label='Y'                       group=Position ");
  TwAddVarRW(bodyGUI, "bdvelx", TW_TYPE_DOUBLE, &abVelocityX_I,     " min=-3E8  max=3E8  step=1 precision=7   label='X'                       group=Velocity ");
  TwAddVarRW(bodyGUI, "bdvely", TW_TYPE_DOUBLE, &abVelocityY_I,     " min=-3E8  max=3E8  step=1 precision=7   label='Y'                       group=Velocity ");
  TwAddVarRO(bodyGUI, "bdaccx", TW_TYPE_DOUBLE, &abAccelerationX_I, "                           precision=7   label='X'                       group=Acceleration ");
  TwAddVarRO(bodyGUI, "bdaccy", TW_TYPE_DOUBLE, &abAccelerationY_I, "                           precision=7   label='Y'                       group=Acceleration ");
  TwAddVarRO(bodyGUI, "bdforx", TW_TYPE_DOUBLE, &abForceX_I,        "                           precision=7   label='X'                       group=Force ");
  TwAddVarRO(bodyGUI, "bdfory", TW_TYPE_DOUBLE, &abForceY_I,        "                           precision=7   label='Y'                       group=Force ");

  TwAddButton(bodyGUI,"delbody", deleteBodyButton, this, " label='Delete Body' ");
}
void gui::setupSystemGUI() {
  // Color
  TwDefine(" 'System' color='255 255 255' alpha=150 text=dark");

  // Size
  TwDefine(" 'System' size='300 90'");
  TwDefine(" 'System' position='0 514'");
  TwDefine(" 'System' resizable=false ");
  TwDefine(" 'System' valueswidth=100 ");
  TwDefine(" 'System' movable=false");
  TwDefine(" 'System' refresh=0.01");

  TwCopyStdStringToClientFunc(handleFilename);
  TwAddVarRW(systemGUI, "filenm", TW_TYPE_STDSTRING, &fileName,  " label='File Name' ");
  TwAddButton(systemGUI,"savebn", saveFileButton, this, " label='Save Scenario' ");
  TwAddButton(systemGUI,"loadbn", loadFileButton, this, " label='Load Scenario' ");
}

void gui::updateActiveID(int p_bodyID) {
  if(p_bodyID != -1) abID_I = p_bodyID;
}

// Class External Callbacks
void TW_CALL saveFileButton(void *cData) {
  gui *iface = static_cast<gui*>(cData); // scene pointer is stored in clientData
  std::cerr << "Saving File: " << iface->fileName << std::endl;
}

void TW_CALL loadFileButton(void *cData) {
  gui *iface = static_cast<gui*>(cData); // scene pointer is stored in clientData
  std::cerr << "Loading File: " << iface->fileName << std::endl;
}

void TW_CALL handleFilename(std::string& destinationClientString, const std::string& sourceLibraryString) {
  // Copy the content of souceString handled by the AntTweakBar library
  destinationClientString = sourceLibraryString;

  if(sourceLibraryString == "") {
    destinationClientString = "Default.sav";
  } else {
    for(int itr = destinationClientString.size(); itr > 0; itr--) {
      if(sourceLibraryString[itr] == '.') {
        destinationClientString = destinationClientString.erase(itr, destinationClientString.size());
        itr = 0;
      }
    }
    destinationClientString = destinationClientString+".sav";
  }
}

void TW_CALL deleteBodyButton(void *cData) {
  gui *iface = static_cast<gui*>(cData);
}

void TW_CALL newBodyButton(void *cData) {

}

void TW_CALL newSuperStructureButton(void *cData) {

}
