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

  // Setup Scenario and Commit
  renderMain.setupDefaultScenario();
  renderMain.updateSharedArea(&sharedData);

  // Create Interface Object
  interface interfaceMain(wXRes, wYRes);
  interfaceMain.updateInterface(&renderMain);

  // Start Sim Thread, Pass SharedData Address
  std::thread simThread(simInit, &sharedData);

  // Configure Projection Matrix, adapt to current resolution.
  initDisplay(wXRes, wYRes);

  setCallbacks(echoWindow);

  while(!glfwWindowShouldClose(echoWindow)) {
    renderMain.updateSharedControl(&sharedData);
    sharedData.setStatus(interfaceMain.getPaused(), 0);

    if(!interfaceMain.getPaused()) {
      // Get New data from Sim if not paused
      std::cerr << "Render Update from Shared" << std::endl;
      renderMain.updateLocalStore(&sharedData);
    } else {
      // Send data to Sim if paused
      std::cerr << "Render Update to Shared" << std::endl;
      renderMain.updateSharedArea(&sharedData);
    }

    // Draw and Display
    displayLoopCall(echoWindow, &renderMain, &interfaceMain);

    if(shouldCheck) {
      double X, Y, aX, aY;
      glfwGetCursorPos(echoWindow, &X, &Y);
      getCoord(X, Y, aX, aY);
      shouldCheck = false;

      // Get Selected Body
      interfaceMain.updateActiveID(renderMain.checkCoord(aX, aY));
      // Update Variables for Body
      interfaceMain.updateInterface(&renderMain);
    }
    // Only Update Body Data if Sim is Paused
    if(interfaceMain.getPaused()) {
      interfaceMain.updateScenario(&renderMain);
    }
    interfaceMain.updateControl(&renderMain);
    // Update Display
    interfaceMain.updateInterface(&renderMain);
  }

  // Exit Procedure
  // Unset Paused and Set Exit Flag
  sharedData.setStatus(false, 0);
  sharedData.setStatus(true, 1);
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

  // Save Default Matrixmk
  glPushMatrix();

  // Set Clear Color for Window
  glClearColor(0.0f, 0.0f, 0.0f, 1);
}

void displayLoopCall(GLFWwindow* localWindow, rdr_obj* renderAccess, interface* interfaceAccess) {
  // Clear Display for Rendering
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixCamera(localWindow);

  // Draw Scene
  renderAccess->drawScene();

  // Draw Tweak Bars
  TwDraw();

  // Swap Render / Draw Buffers
  glfwSwapBuffers(localWindow);

  // Check For Input Events
  glfwPollEvents();
}
