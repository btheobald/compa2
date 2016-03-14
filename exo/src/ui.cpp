// Interface include
#include "ui.hpp"
// External library includes
#include <AntTweakBar.h>  // AntTweakBar
#include <GL/glu.h>       // GLU

// Render access pointer
render* g_RenderAP;

// GUI pointers
TwBar* simGUI;
TwBar* bodyGUI;
TwBar* ssGUI;

// Active Body
body* activeBody;
int activeID;
int bodyCount;

double vectX = 0, vectY = 0;
double scaleFactor = 1;
double responsiveness = 2;

// global superstructure creation gui - this file only
struct ss {
  int bodies = 100;
  double cMass = 10000;
  double oMass = 0.1;
  double cRadius = 5;
  double oRadius = 0.1;

  double cPX = 0;
  double cPY = 0;

  double cVX = 0;
  double cVY = 0;

  double spacing = 50;
  double radius = 200;
} ss;

// Applys camera transform and scale
void applyCamera(void) {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glScaled(scaleFactor, scaleFactor, 1);

  glTranslated(-vectX, vectY, 0);

  glPushMatrix();
}

// Custom Inputs
// Returns true if mouse button held.
bool getMouseHeld(GLFWwindow* window, int button) {
  static bool checking;
  static bool held;
  static double startTime;

  if((glfwGetMouseButton(window, button) == GLFW_PRESS)) {
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

// Input
void cursorPosCallback(GLFWwindow* window, double cursorX, double cursorY) {
  // Pass event to AntTweakBar
  if(!TwEventMousePosGLFW(cursorX, cursorY)) {
    // If not handled by AntTweakBar
    moveCamera(window, cursorX, cursorY);
  }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  // Pass event to AntTweakBar
  if(!TwEventMouseButtonGLFW(button, action)) {
    // If not handled by AntTweakBar
    if((action == GLFW_PRESS) & (button == 0)) {
      double aX, aY;
      getCoord(window, aX, aY);
      int id = g_RenderAP->checkCoord(aX, aY, (1/scaleFactor)*10);
      if(id != -1) {
        activeID = id;
        updateUI(g_RenderAP);
      }
    }
  }
}

void mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
  // Pass event to AntTweakBar
  if(!TwEventMouseWheelGLFW(yOffset)) {
    // If not handled by AntTweakBar
    zoomCamera(yOffset);
  }
}

void keyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  // Pass event to AntTweakBar
  if(!TwEventKeyGLFW(key, action)) {
    // If not handled by AntTweakBar
    //TODO: Add keyboard shortcuts
  }
}

void keyboardCharCallback(GLFWwindow* window, unsigned int codepoint) {
  // Pass event to AntTweakBar
  if(!TwEventCharGLFW(codepoint, GLFW_PRESS)) {
    // If not handled by AntTweakBar
    //TODO: Add keyboard shortcuts
  }
}

// Window
void windowResizeCallback(GLFWwindow* window, int width, int height) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-width, width, -height, height, 1.0f, -1.0f);

  applyCamera();

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

void updateUI(render* renderAP) {
  // Free memory used by previous
  delete activeBody;

  // Update Body Count
  bodyCount = renderAP->pBodies.size();

  if(bodyCount != 0) {
    // Update Body Interface
    activeBody = new body(renderAP->pBodies[activeID]);
  } else {
    // Generate Null Body
    activeBody = new body();
    activeID = 0;
  }
}

void updateBody(render* renderAP) {
  if(bodyCount != 0) {
    renderAP->updateBody(activeBody, activeID);
  }
}

// AntTweakBar functions
void TW_CALL deleteBodyButton(void *cData) {
  // Only delete body if there are bodies to delete
  if(bodyCount != 0) {
    // Retrieve pointer from clientData container.
    render *renderContainer = static_cast<render*>(cData);
    // Call Delete of selected body
    renderContainer->delBody(activeID);
    // Update render container to next or null body.
    updateUI(renderContainer);
  }
}

void TW_CALL deleteAllBodiesButton(void *cData) {
  // Retrieve pointer from clientData container.
  render *renderContainer = static_cast<render*>(cData);
  // Call Delete All Bodies
  renderContainer->deleteAllBodies();
  // Update render container to populate initial null body.
  updateUI(renderContainer);
}

void TW_CALL newBodyButton(void *cData) {
  // Retrieve pointer from clientData container.
  render *renderContainer = static_cast<render*>(cData);
  // Create new body in render.
  renderContainer->addBody(new body(1, 1, 0, 0, 0, 0));
  // Update UI to update body count.
  updateUI(renderContainer);
}

void TW_CALL newSuperStructureButton(void *cData) {
  // Retrieve pointer from clientData container.
  render *renderContainer = static_cast<render*>(cData);
  // Create superstructure
  renderContainer->createSuperstructure(ss.bodies, ss.cMass, ss.oMass, ss.cRadius, ss.oRadius, ss.cPX, ss.cPY, ss.cVX, ss.cVY, ss.spacing, ss.radius);
  // Update UI to update body count.
  updateUI(renderContainer);
}

void setupSimGUI(render* renderAP) {
  // Color
  TwDefine(" 'Simulation' color='255 255 255' alpha=150 text=dark");

  // Size
  TwDefine(" 'Simulation' size='300 180'");
  TwDefine(" 'Simulation' position='0 0'");
  TwDefine(" 'Simulation' resizable=true ");
  TwDefine(" 'Simulation' valueswidth=100 ");
  TwDefine(" 'Simulation' movable=true");
  TwDefine(" 'Simulation' refresh=0.01");

  // Control
  TwAddVarRW(simGUI, "ugcvar", TW_TYPE_DOUBLE,  &renderAP->pControl.UGC,        " min=1E-12  max=10   step=0.01  precision=7   label='Gravitational Constant'  group=Control ");
  TwAddVarRW(simGUI, "idtvar", TW_TYPE_DOUBLE,  &renderAP->pControl.IDT,        " max=-1E9   max=1E15  step=0.01  precision=7  label='Itteration Delta Time'   group=Control ");
  TwAddVarRW(simGUI, "collid", TW_TYPE_BOOLCPP, &renderAP->pControl.collide,    " true=On      false=Off                       label='Simulate Collisions'     group=Control ");
  // Runtime
  TwAddVarRW(simGUI, "paused", TW_TYPE_BOOLCPP, &renderAP->pControl.paused,     " true=Paused  false=Running                   label='Run/Pause'               group=Runtime ");
  TwAddVarRW(simGUI, "ipfvar", TW_TYPE_INT32,   &renderAP->pControl.IPF,        " min=1      max=10000  step=1                 label='Itterations Per Frame'   group=Runtime ");
  // Statistics
  TwAddVarRO(simGUI, "numbod", TW_TYPE_INT32,   &bodyCount,                     "                                              label='Number of Bodies'        group=Statistics ");
}

void setupBodyGUI(render* renderAP) {
  // Set Default Body
  activeID = 0;
  updateUI(renderAP);

  // Color
  TwDefine(" 'Body' color='255 255 255' alpha=150 text=dark");

  // Size
  TwDefine(" 'Body' size='300 400'");
  TwDefine(" 'Body' position='0 182'");
  TwDefine(" 'Body' resizable=true ");
  TwDefine(" 'Body' valueswidth=100 ");
  TwDefine(" 'Body' movable=true");
  TwDefine(" 'Body' refresh=0.01");

  TwAddVarRO(bodyGUI, "bodyid", TW_TYPE_INT32,   &activeID,          "                                              label='Selected Body ID' ");
  TwAddVarRW(bodyGUI, "bdmass", TW_TYPE_DOUBLE,  &activeBody->m,     " min=1E-3  max=1E40 step=1      precision=4   label='Mass'                    group=Properties ");
  TwAddVarRW(bodyGUI, "bdradi", TW_TYPE_DOUBLE,  &activeBody->r,     " min=1E-3  max=1E14 step=1      precision=4   label='Radius'                  group=Properties ");
  TwAddVarRW(bodyGUI, "bdfixd", TW_TYPE_BOOLCPP, &activeBody->fixed, " true=Yes      false=No                       label='Fixed'                   group=Properties ");
  TwAddVarRW(bodyGUI, "bdcolr", TW_TYPE_COLOR3F, &activeBody->color, " coloralpha=false                             label='Colour'                  group=Properties ");

  TwAddVarRW(bodyGUI, "bdposx", TW_TYPE_DOUBLE,  &activeBody->pX,    " min=-1E15 max=1E15 step=0.01 precision=5     label='X'                       group=Position ");
  TwAddVarRW(bodyGUI, "bdposy", TW_TYPE_DOUBLE,  &activeBody->pY,    " min=-1E15 max=1E15 step=0.01 precision=5     label='Y'                       group=Position ");
  TwAddVarRW(bodyGUI, "bdvelx", TW_TYPE_DOUBLE,  &activeBody->vX,    " min=-3E8  max=3E8  step=0.01 precision=5     label='X'                       group=Velocity ");
  TwAddVarRW(bodyGUI, "bdvely", TW_TYPE_DOUBLE,  &activeBody->vY,    " min=-3E8  max=3E8  step=0.01 precision=5     label='Y'                       group=Velocity ");
  TwAddVarRO(bodyGUI, "bdaccx", TW_TYPE_DOUBLE,  &activeBody->aX,    "                              precision=5     label='X'                       group=Acceleration ");
  TwAddVarRO(bodyGUI, "bdaccy", TW_TYPE_DOUBLE,  &activeBody->aY,    "                              precision=5     label='Y'                       group=Acceleration ");

  TwAddButton(bodyGUI,"newbody", newBodyButton, renderAP,            " label='New Body'          group=Management ");
  TwAddButton(bodyGUI,"delbody", deleteBodyButton, renderAP,         " label='Delete Body'       group=Management ");
  TwAddButton(bodyGUI,"delallb", deleteAllBodiesButton, renderAP,    " label='Delete All'        group=Management ");
}

void setupSuperStructGUI(render* renderAP) {
  // Color
  TwDefine(" 'Superstructure' color='255 255 255' alpha=150 text=dark");

  // Size
  TwDefine(" 'Superstructure' iconified=true");
  TwDefine(" 'Superstructure' size='300 300'");
  TwDefine(" 'Superstructure' position='300 0'");
  TwDefine(" 'Superstructure' resizable=true ");
  TwDefine(" 'Superstructure' valueswidth=100 ");
  TwDefine(" 'Superstructure' movable=true");
  TwDefine(" 'Superstructure' refresh=0.01");

  TwAddVarRW(ssGUI, "nbodies", TW_TYPE_INT32,  &ss.bodies,  " min=1     max=8000  step=1     precision=4   label='# of Outer Bodies' group='System'");
  TwAddVarRW(ssGUI, "sradius", TW_TYPE_DOUBLE, &ss.radius,  " min=1E-4  max=1E14  step=0.1   precision=4   label='System Radius' group='System'");
  TwAddVarRW(ssGUI, "cospace", TW_TYPE_DOUBLE, &ss.spacing, " min=0     max=3E8   step=0.1   precision=4   label='Central/Outer Spacing' group='System'");

  TwAddVarRW(ssGUI, "cmass",   TW_TYPE_DOUBLE, &ss.cMass,   " min=1E-4  max=1E40  step=0.01  precision=4   label='Mass'   group='Central Body'");
  TwAddVarRW(ssGUI, "cradi",   TW_TYPE_DOUBLE, &ss.cRadius, " min=1E-4  max=1E14  step=0.01  precision=4   label='Radius' group='Central Body'");

  TwAddVarRW(ssGUI, "omass",   TW_TYPE_DOUBLE, &ss.oMass,   " min=1E-4  max=1E40  step=0.01  precision=4   label='Mass'   group='Outer Body'");
  TwAddVarRW(ssGUI, "oradi",   TW_TYPE_DOUBLE, &ss.oRadius, " min=1E-4  max=1E14  step=0.01  precision=4   label='Radius' group='Outer Body'");

  TwAddVarRW(ssGUI, "cposx",   TW_TYPE_DOUBLE, &ss.cPX,     " min=-1E16 max=1E16  step=0.01  precision=4   label='X' group='Central Position'");
  TwAddVarRW(ssGUI, "cposy",   TW_TYPE_DOUBLE, &ss.cPY,     " min=-1E16 max=1E16  step=0.01  precision=4   label='Y' group='Central Position'");

  TwAddVarRW(ssGUI, "cvelx",   TW_TYPE_DOUBLE, &ss.cVX,     " min=-3E8  max=3E8   step=0.01  precision=4   label='X' group='Central Velocity'");
  TwAddVarRW(ssGUI, "cvely",   TW_TYPE_DOUBLE, &ss.cVY,     " min=-3E8  max=3E8   step=0.01  precision=4   label='Y' group='Central Velocity'");

  TwAddButton(ssGUI,"cssbt", newSuperStructureButton, renderAP, " label='Create Superstructure'");
}

void setupGUI(GLFWwindow* window, render* renderAP) {
  // Set global render pointer
  g_RenderAP = renderAP;

  // Get GLFW window size
  int wX, wY;
  glfwGetWindowSize(window, &wX, &wY);

  // Init AntTweakBar
  TwInit(TW_OPENGL, NULL);
  TwWindowSize(wX, wY);

  // Setup GUIs
  simGUI = TwNewBar("Simulation");
  bodyGUI = TwNewBar("Body");
  ssGUI = TwNewBar("Superstructure");
  setupSimGUI(renderAP);
  setupBodyGUI(renderAP);
  setupSuperStructGUI(renderAP);

  // Set Globals
  TwDefine(" GLOBAL contained=true ");
  TwDefine(" GLOBAL fontresizable=false ");
  TwDefine(" GLOBAL fontstyle=default ");
  TwDefine(" GLOBAL buttonalign=center");
}
