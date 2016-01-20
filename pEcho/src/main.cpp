#include <GLFW/glfw3.h>
//#include "callbacks.h"
#include <iostream>
#include <thread>

#include "simEntry.h"

using namespace std;

int main() {
  // Init GLFW
  int wXRes = 960;
  int wYRes = 480;
  GLFWwindow* echoWindow;

  // Framerate Variables
  double fcStartTime;
  int frameCounter = 0;

  // Init GLFW
  glfwInit();
  echoWindow = glfwCreateWindow(wXRes, wYRes, "Test Window", NULL, NULL);
  glfwMakeContextCurrent(echoWindow);

  // TODO: Init AntTweakBar
  // TODO: Create Tweakbar and Add Variables?

  // Start Sim Thread
  thread simThread(simInit);
  // TODO: Thread Sync

  // Initial Framerate Timer Set
  fcStartTime = glfwGetTime();

  while(!glfwWindowShouldClose(echoWindow)) {
    // Set Clear Color for Window
    glClearColor(0.05f, 0.05f, 0.1f, 1);
    // Clear Display for Rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Init Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, wXRes, wYRes, 0.0f, 1.0f, -1.0f);

    // Init Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // TODO: Get New Sim Data
    // TODO: Calculate Display Based on Camera Position and Size.
    // TODO: Render Here

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

  // Pause until simInit Exits.
  simThread.join();
  // Keep window open until simThread exits.
  glfwTerminate();
  return 0;
}
