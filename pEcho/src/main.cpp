#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>

#include "sharedStage.hpp"
#include "simEntry.hpp"
#include "rdr_obj.hpp"
#include <AntTweakBar.h>

using namespace std;

void initMatrix(int lXRes, int lYRes);
void setupDefaultScenario(rdr_obj* l_RenderMain);
void updateSharedArea(rdr_obj* l_RenderMain, sharedStage* l_sharedDataAccess);
void updateLocalStore(sharedStage* l_sharedDataAccess, rdr_obj* l_RenderMain);

int main() {
  // Init Render Scenario and Access Pointer
  rdr_obj renderMain;
  rdr_obj* renderMainAccess = &renderMain;
  // Init Shared Stage and Access Pointer
  sharedStage sharedData;
  sharedStage* sharedDataAccess = &sharedData;
  setupDefaultScenario(renderMainAccess);
  updateSharedArea(renderMainAccess, sharedDataAccess);

  // Init GLFW
  int wXRes = 960;
  int wYRes = 480;
  GLFWwindow* echoWindow;

  // Framerate Variables
  double fcStartTime;
  int frameCounter = 0;

  // Init GLFW
  glfwInit();
  echoWindow = glfwCreateWindow(wXRes, wYRes, "Echo", NULL, NULL);
  glfwMakeContextCurrent(echoWindow);

  // Init AntTweakBar
  TwBar *test;
  TwInit(TW_OPENGL, NULL);
  TwWindowSize(wXRes, wYRes);
  test = TwNewBar("Test");

  // Start Sim Thread, Pass SharedData Address
  thread simThread(simInit, sharedDataAccess);

  // Initial Framerate Timer Set
  fcStartTime = glfwGetTime();

  while(!glfwWindowShouldClose(echoWindow)) {
    // Set Clear Color for Window
    glClearColor(0.05f, 0.05f, 0.1f, 1);
    // Clear Display for Rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Configure Projection Matrix, adapt to current resolution.
    initMatrix(wXRes, wYRes);

    // TODO: Get New Sim Data
    // TODO: Calculate Display Based on Camera Position and Size.
    // TODO: Render Here
    renderMainAccess -> drawBody(0);
    renderMainAccess -> drawBody(1);
    renderMainAccess -> drawBody(2);
    renderMainAccess -> drawBody(3);
    renderMainAccess -> drawBody(4);
    renderMainAccess -> drawBody(5);
    renderMainAccess -> drawBody(6);
    renderMainAccess -> drawBody(7);

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
      cerr << frameCounter << "FPS, "<< 1000.0/(double)frameCounter << "ms" << endl;
      frameCounter = 0;
      fcStartTime = glfwGetTime();
    }

    updateLocalStore(sharedDataAccess, renderMainAccess);
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
  glOrtho(-lXRes/2, lXRes/2, -lYRes/2, lYRes/2, 1.0f, -1.0f);

  // Init Modelview Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void setupDefaultScenario(rdr_obj* l_RenderMain) {
  // Bodies
  l_RenderMain -> newBody(1000.0, 5.0, 0.0, 0.0, 0.0, 0.0);
  l_RenderMain -> newBody(1.0, 3.0, 80.0, 0.0, 0.0, 1.00);
  l_RenderMain -> newBody(1.0, 3.0, 62.0, 20.0, 0.0, 1.00);
  l_RenderMain -> newBody(1.0, 3.0, -42.0, 56.0, 0.0, -1.00);
  l_RenderMain -> newBody(1.0, 3.0, -23.0, -30.0, 0.0, 2.00);
  l_RenderMain -> newBody(1.0, 3.0, 23.0, -10.0, 0.0, 2.00);
  l_RenderMain -> newBody(1.0, 3.0, 13.0, -55.0, 0.0, 1.00);
  l_RenderMain -> newBody(1.0, 3.0, 50.0, -20.0, 0.0, 1.00);
  // Simulation Control
  l_RenderMain -> setUGC(0.1);
  l_RenderMain -> setIDT(0.001);
  l_RenderMain -> setIPF(1000);
}

void updateSharedArea(rdr_obj* l_RenderMain, sharedStage* l_sharedDataAccess) {
  // Push Body Data To Shared
  l_sharedDataAccess -> populateBodyStore_R(l_RenderMain -> returnBodyStore());
  // Push Simulation Control To Shared
  l_sharedDataAccess -> setUGC(l_RenderMain -> getUGC());
  l_sharedDataAccess -> setIDT(l_RenderMain -> getIDT());
  l_sharedDataAccess -> setIPF(l_RenderMain -> getIPF());
  // Unpause Sim
  l_sharedDataAccess -> setStatus(0, false);
}

void updateLocalStore(sharedStage* l_sharedDataAccess, rdr_obj* l_RenderMain) {
  // Push Body Data To Shared
  if(l_sharedDataAccess -> newSScenarioCheck()) {
    l_RenderMain -> populateBodyStore(l_sharedDataAccess -> returnBodyStore_S());
    l_sharedDataAccess -> simWait.notify_all();
  }
}
