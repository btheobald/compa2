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
void setupDefaultScenario(rdr_obj* l_RenderMain);
void updateSharedArea(rdr_obj* l_RenderMain, sharedStage* l_sharedDataAccess);
void updateLocalStore(sharedStage* l_sharedDataAccess, rdr_obj* l_RenderMain);

int main() {
  // Set Random Seed Using Current Time
  srand(time(NULL));

  // Init Render Scenario and Access Pointer
  rdr_obj renderMain;
  rdr_obj* renderMainAccess = &renderMain;
  // Init Shared Stage and Access Pointer
  sharedStage sharedData;
  sharedStage* sharedDataAccess = &sharedData;
  setupDefaultScenario(renderMainAccess);
  updateSharedArea(renderMainAccess, sharedDataAccess);

  // Init GLFW
  //int wXRes = 1366;
  //int wYRes = 768;
  int wXRes = 1920;
  int wYRes = 1080;
  GLFWwindow* echoWindow;

  // Framerate Variables
  double fcStartTime;
  int frameCounter = 0;

  // Init GLFW
  glfwInit();
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_REFRESH_RATE, 60);
  echoWindow = glfwCreateWindow(wXRes, wYRes, "Echo", glfwGetPrimaryMonitor(), NULL);
  glfwMakeContextCurrent(echoWindow);
  // Init AntTweakBar
  TwBar *test;
  TwInit(TW_OPENGL, NULL);
  TwWindowSize(wXRes, wYRes);
  test = TwNewBar("Test");

  // Start Sim Thread, Pass SharedData Address
  std::thread simThread(simInit, sharedDataAccess);

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
    for(int bIDC = 0; bIDC < 1201; bIDC++) {
      renderMainAccess->drawBody(bIDC);
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
  // Simulation Control
  l_RenderMain -> setUGC(0.1);
  l_RenderMain -> setIDT(0.1);
  l_RenderMain -> setIPF(1);

  // Bodies
  double tempPosX, tempPosY, tempDist, tempVelX, tempVelY;
  l_RenderMain -> newBody(100000, 5, 0, 0, 0, 0);
  for(int bIDC = 0; bIDC < 1200; bIDC++) {
    tempPosX = ((double)(rand() % 300)-150)+(((double)(rand() % 200)-100)/100);
    tempPosY = ((double)(rand() % 300)-150)+(((double)(rand() % 200)-100)/100);
    tempDist = sqrt(pow(tempPosX,2) + pow(tempPosY,2));
    tempVelY = copysign(sqrt((l_RenderMain->getUGC()*100000) / pow(tempDist,3)) * tempPosY, tempPosX);
    tempVelX = copysign(sqrt((l_RenderMain->getUGC()*100000) / pow(tempDist,3)) * tempPosX, -tempPosY);
    l_RenderMain -> newBody(0.1, 1, tempPosX, tempPosY, tempVelX, tempVelY);
  }
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
