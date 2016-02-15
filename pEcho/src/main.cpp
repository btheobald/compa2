// Standard Library Includes
#include <thread>
#include <iostream>
// External Library Includes
#include <GLFW/glfw3.h>   // GLFW
#include <AntTweakBar.h>  // AntTweakBar
// Custom Includes
#include "rdr_obj.hpp"
#include "sharedStage.hpp"
#include "simEntry.hpp"
#include "handling.hpp"

bool shouldCheck;

void initDisplay(int lXRes, int lYRes);
void displayLoopCall(GLFWwindow* localWindow, rdr_obj* renderAccess);

int main() {
  // Set Random Seed Using Current Time
  srand(time(NULL));

  // Init Render Scenario
  rdr_obj renderMain;
  // Init Shared Stage
  sharedStage sharedData;

  // Init GLFW
  glfwInit();
  // MSSA 8X
  glfwWindowHint(GLFW_SAMPLES,8);
  // Create Window
  GLFWwindow* echoWindow;
  // Get User Resolution
  const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  int wXRes = mode->width/1.2;
  int wYRes = mode->height/1.2;

  echoWindow = glfwCreateWindow(wXRes, wYRes, "Echo", NULL, NULL);
  glfwMakeContextCurrent(echoWindow);

  // Init AntTweakBar
  TwBar* controls;
  TwInit(TW_OPENGL, NULL);
  TwWindowSize(wXRes, wYRes);
  controls = TwNewBar("Controls");
  double UGC = 6E-11;
  double IDT = 1E12;
  int IPF = 1;
  renderMain.updateLocalControl(UGC, IDT, IPF);
  TwAddVarRW(controls, "UGC", TW_TYPE_DOUBLE, &UGC, " min=1E-12 max=10 step=0.01 group=Engine label='Graviational Constant' ");
  TwAddVarRW(controls, "IDT", TW_TYPE_DOUBLE, &IDT, " min=-1000 max=1E20 step=0.01 group=Engine label='Itteration Delta Time' ");
  TwAddVarRW(controls, "IPF", TW_TYPE_INT32, &IPF,  " min=1 max=1000 step=1 group=Engine label='Itterations Per Frame' ");

  // Setup Scenario and Commit
  renderMain.setupDefaultScenario();
  renderMain.updateSharedArea(&sharedData);

  // Start Sim Thread, Pass SharedData Address
  std::thread simThread(simInit, &sharedData);

  // Configure Projection Matrix, adapt to current resolution.
  initDisplay(wXRes, wYRes);

  setCallbacks(echoWindow);

  while(!glfwWindowShouldClose(echoWindow)) {
    renderMain.updateLocalControl(UGC, IDT, IPF);
    renderMain.updateSharedControl(&sharedData);
    // Pull Changes from Shared
    renderMain.updateLocalStore(&sharedData);

    // Draw and Display
    displayLoopCall(echoWindow, &renderMain);

    // TODO: Update Local Scenario with Changes
  }

  // Exit Procedure
  // TODO: Save Data to startup file here
  // Unset Paused and Set Exit Flag
  sharedData.setStatus(0, false);
  sharedData.setStatus(1, true);
  // Resume Thread if Waiting
  sharedData.simWait.notify_all();
  // Pause until simInit Exits.
  simThread.join();
  std::cerr << "Sim Exit" << std::endl;

  // Keep window open until simThread exits.
  glfwTerminate();
  return 0;
}

void initDisplay(int lXRes, int lYRes) {
  glEnable(GL_DEPTH);
  // Init Projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-lXRes, lXRes, -lYRes, lYRes, 1.0f, -1.0f);

  // Init Modelview
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Set Viewport Extents
  glViewport(0, 0, lXRes, lYRes);

  // Save Default Matrix
  glPushMatrix();

  // Set Clear Color for Window
  //glClearColor(0.05f, 0.05f, 0.1f, 1);
  glClearColor(0.0f, 0.0f, 0.0f, 1);
}

void displayLoopCall(GLFWwindow* localWindow, rdr_obj* renderAccess) {
  // Clear Display for Rendering
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Draw Scene
  renderAccess->drawScene();

  // Draw Tweak Bars
  TwDraw();

  matrixCamera(localWindow);

  if(shouldCheck) {
    double X, Y, aX, aY;
    glfwGetCursorPos(localWindow, &X, &Y);
    getCoord(X, Y, aX, aY);
    std::cerr << renderAccess->checkCoord(aX, aY) << std::endl;
    shouldCheck = false;
  }

  // Swap Render / Draw Buffers
  glfwSwapBuffers(localWindow);

  // Check For Input Events
  glfwPollEvents();
}
