#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>

#include "sharedStage.hpp"
#include "simEntry.hpp"
#include "rdr_obj.cpp"
#include <AntTweakBar.h>

using namespace std;

void initMatrix(int lXRes, int lYRes);
void setupDefaultScenario(rdr_obj* l_RenderMain);
void updateSharedArea(rdr_obj* l_RenderMain, sharedStage* l_sharedDataAccess);

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
  // TODO: Thread Syncup

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
  glOrtho(0.0f, lXRes, lYRes, 0.0f, 1.0f, -1.0f);

  // Init Modelview Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void setupDefaultScenario(rdr_obj* l_RenderMain) {
  l_RenderMain -> newBody(1000.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  l_RenderMain -> newBody(1.0, 0.0, 100.0, 0.0, 0.0, 1.001);
}

void updateSharedArea(rdr_obj* l_RenderMain, sharedStage* l_sharedDataAccess) {
  l_sharedDataAccess -> populateBodyStore_R(l_RenderMain -> returnBodyStore());
}
