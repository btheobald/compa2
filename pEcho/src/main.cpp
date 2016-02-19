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
#include "interface.hpp"

bool shouldCheck;

void initDisplay(int lXRes, int lYRes);
void displayLoopCall(GLFWwindow* localWindow, rdr_obj* renderAccess, interface* interfaceAccess);

int main() {
  // Create Render Thread Local Class
  rdr_obj renderMain;
  // Create Shared Stage Object
  sharedStage sharedData;

  // Init GLFW
  glfwInit();
  // MSSA 8X
  glfwWindowHint(GLFW_SAMPLES,8);
  // Create Window
  GLFWwindow* echoWindow;
  // Get User Resolution
  const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  int wXRes = mode->width*0.8;
  int wYRes = mode->height*0.8;

  echoWindow = glfwCreateWindow(wXRes, wYRes, "Echo", NULL, NULL);
  glfwMakeContextCurrent(echoWindow);

  // Create Interface Object
  interface localInterface(wXRes, wYRes);

  // Setup Scenario and Commit
  renderMain.setupDefaultScenario();
  renderMain.updateSharedArea(&sharedData);

  // Start Sim Thread, Pass SharedData Address
  std::thread simThread(simInit, &sharedData);

  // Configure Projection Matrix, adapt to current resolution.
  initDisplay(wXRes, wYRes);

  setCallbacks(echoWindow);

  while(!glfwWindowShouldClose(echoWindow)) {
    //renderMain.updateLocalControl(UGC, IDT, IPF);
    renderMain.updateSharedControl(&sharedData);
    // Pull Changes from Shared
    renderMain.updateLocalStore(&sharedData);

    // Draw and Display
    displayLoopCall(echoWindow, &renderMain, &localInterface);

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
  TwTerminate();
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

void displayLoopCall(GLFWwindow* localWindow, rdr_obj* renderAccess, interface* interfaceAccess) {
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
    //std::cerr << renderAccess->checkCoord(aX, aY) << std::endl;
    shouldCheck = false;

    interfaceAccess->updateActiveID(renderAccess->checkCoord(aX, aY));
  }
  interfaceAccess->updateInterface(renderAccess);

  // Swap Render / Draw Buffers
  glfwSwapBuffers(localWindow);

  // Check For Input Events
  glfwPollEvents();
}
