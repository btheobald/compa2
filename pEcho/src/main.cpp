// Standard Library Includes
#include <thread>
#include <cstdlib>
#include <cmath>
#include <ctime>
// External Library Includes
#include <GLFW/glfw3.h>
#include <AntTweakBar.h>
// Custom Includes
#include "rdr_obj.hpp"
#include "sharedStage.hpp"
#include "simEntry.hpp"

void initMatrix(int lXRes, int lYRes);

int main() {
  // Set Random Seed Using Current Time
  srand(time(NULL));

  // Init Render Scenario and Access Pointer
  rdr_obj renderMain;
  // Init Shared Stage and Access Pointer
  sharedStage sharedData;
  sharedStage* sharedDataAccess = &sharedData;

  // Setup Scenario and Commit
  renderMain.setupDefaultScenario();
  renderMain.updateSharedArea(sharedDataAccess);

  // Init GLFW
  int wXRes = 1366;
  int wYRes = 768;
  //int wXRes = 1920;
  //int wYRes = 1080;
  GLFWwindow* echoWindow;

  // Framerate Variables
  double fcStartTime;
  int frameCounter = 0;

  // Init GLFW
  glfwInit();
  // MSSA 8X
  glfwWindowHint(GLFW_SAMPLES, 8);
  // Create Window
  echoWindow = glfwCreateWindow(wXRes, wYRes, "Echo", glfwGetPrimaryMonitor(), NULL);
  glfwMakeContextCurrent(echoWindow);

  // Init AntTweakBar
  TwBar* test;
  TwInit(TW_OPENGL, NULL);
  TwWindowSize(wXRes, wYRes);
  test = TwNewBar("Test");

  // Start Sim Thread, Pass SharedData Address
  std::thread simThread(simInit, sharedDataAccess);

  // Initial Framerate Timer Set
  fcStartTime = glfwGetTime();

  while(!glfwWindowShouldClose(echoWindow)) {
    // Pull Changes from Shared
    renderMain.updateLocalStore(sharedDataAccess);

    // Set Clear Color for Window
    glClearColor(0.05f, 0.05f, 0.1f, 1);
    // Clear Display for Rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Configure Projection Matrix, adapt to current resolution.
    initMatrix(wXRes, wYRes);

    // Draw Bodies
    for(int bIDC = 0; bIDC < 1201; bIDC++) {
      renderMain.drawBody(bIDC);
    }

    // Draw Tweak Bars
    TwDraw();
    // Swap Render / Draw Buffers
    glfwSwapBuffers(echoWindow);
    // TODO: Poll Input Events
    glfwPollEvents();
    // TODO: Update Local Scenario with Changes

    // Increment Frame Counter
    frameCounter++;
    // Check if 1 Second has Passed
    if(glfwGetTime() - fcStartTime >= 1.0) {
      frameCounter = 0;
      fcStartTime = glfwGetTime();
    }
  }

  // Set Exit Flag
  sharedData.setStatus(1, true);
  // Pause until simInit Exits.
  simThread.join();
  
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