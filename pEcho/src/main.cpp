// Standard Library Includes
#include <thread>
// External Library Includes
#include <GLFW/glfw3.h>   // GLFWW
#include <AntTweakBar.h>  // AntTweakBar
// Custom Includes
#include "rdr_obj.hpp"
#include "sharedStage.hpp"
#include "simEntry.hpp"

void initMatrix(int lXRes, int lYRes);
void displayLoopCall(GLFWwindow* localWindow, rdr_obj* renderAccess);

int main() {
  // Set Random Seed Using Current Time
  srand(time(NULL));

  // Init Render Scenario
  rdr_obj renderMain;
  // Init Shared Stage
  sharedStage sharedData;

  // Setup Scenario and Commit
  renderMain.setupDefaultScenario();
  renderMain.updateSharedArea(&sharedData);

  // Init GLFW
  glfwInit();
  // MSSA 8X
  glfwWindowHint(GLFW_SAMPLES, 8);
  // Create Window (Fullscreen)
  GLFWwindow* echoWindow;

  // Get User Resolution
  const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  int wXRes = mode->width/1.2;
  int wYRes = mode->height/1.2;

  echoWindow = glfwCreateWindow(wXRes, wYRes, "Echo", NULL, NULL);
  glfwMakeContextCurrent(echoWindow);

  // Init AntTweakBar
  TwBar* test;
  TwInit(TW_OPENGL, NULL);
  TwWindowSize(wXRes, wYRes);
  test = TwNewBar("Test");

  // Start Sim Thread, Pass SharedData Address
  std::thread simThread(simInit, &sharedData);

  // Configure Projection Matrix, adapt to current resolution.
  initMatrix(wXRes, wYRes);
  // Set Clear Color for Window
  glClearColor(0.05f, 0.05f, 0.1f, 1);


  while(!glfwWindowShouldClose(echoWindow)) {
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

void initMatrix(int lXRes, int lYRes) {
  // Init Projection Matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Center View on 0, 0 and Make Pixel Perfect
  glOrtho(-lXRes/2, lXRes/2, -lYRes/2, lYRes/2, 1.0f, -1.0f);
  
  // Init Modelview Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void displayLoopCall(GLFWwindow* localWindow, rdr_obj* renderAccess) {
  // Clear Display for Rendering
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Draw Scene
  renderAccess->drawScene();

  // Draw Tweak Bars
  TwDraw();

  // Swap Render / Draw Buffers
  glfwSwapBuffers(localWindow);
  // Check For Input Events
  glfwPollEvents();
}