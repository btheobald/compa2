// Standard Library
#include <iostream>
#include <thread>
// External Libraries
#include <GLFW/glfw3.h>
#include <AntTweakBar.h>
// Program Includes
#include "shared.hpp"
#include "simulation.hpp"
#include "render.hpp"
#include "screen.hpp"
#include "body.hpp"
#include "ui.hpp"

// Sim thread startup function
void startup(shared* sharedAP);
GLFWwindow* windowSetup();
void setupDefaultScenario(render* renderAP, shared* sharedAP);

int main() {
  // Setup window and give pointer
  GLFWwindow* window = windowSetup();

  // Create access pointers
  render* renderAP = new render;
  shared* sharedAP = new shared;
  setupDefaultScenario(renderAP, sharedAP);

  // Create simulation thread
  std::thread simThread(startup, sharedAP);

  // Control structure for interface
  control main = renderAP->getControl();

  // Main Runtime Loop
  while(!glfwWindowShouldClose(window)) {
    // Clear screen before drawing
    glClear(GL_COLOR_BUFFER_BIT);

    // Get update from shared
    renderAP->updateBodies(sharedAP->getBodies());
    sharedAP->simWait.notify_all();

    // Render Scene
    renderAP->drawScene();

    applyCamera(window);

    // Display is double buffered to prevent screen tearing
    // Swap display buffers
    glfwSwapBuffers(window);
    // Poll and process events
    glfwPollEvents();
  }

  // Unpause and Exit
  main.paused = false;
  main.exit = true;
  // Control direct to shared
  sharedAP->updateControl(main);
  sharedAP->simWait.notify_all();

  // Program exit
  simThread.join();
  // Delete heap objects
  delete renderAP;
  delete sharedAP;
  // Terminate Libraries
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

GLFWwindow* windowSetup() {
    /*                       */
   // GLFW Init Boilerplate //
  /*                       */
  if(!glfwInit()) {
    // Exit if GLFW does not init
    std::cerr << "GLFW could not init" << std::endl;
    exit(1);
  }

  GLFWwindow* window; // Create window
  glfwWindowHint(GLFW_SAMPLES,8); // MSAA 8x
  // Get user screen resolution
  const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  // Make window smaller than screen
  int wXRes = mode->width * 0.8;
  int wYRes = mode->height * 0.8;

  window = glfwCreateWindow(wXRes, wYRes, "Exo N-Body", NULL, NULL);
  if (!window) {
    // Terminate and exit if window cannot open
    std::cerr << "GLFW could not create window" << std::endl;
    glfwTerminate();
    exit(1);
  }

  glfwMakeContextCurrent(window);
  initDisplay(wXRes, wYRes);
  setCallbacks(window);

  return window;
    /*                       */
   // GLFW Boilerplate End  //
  /*                       */
}

void setupDefaultScenario(render* renderAP, shared* sharedAP) {
  // Tempoary control structure for setup
  control temp;
  temp.UGC = 0.1;
  temp.IDT = 0.1;
  temp.IPF = 1;
  temp.paused = false;
  temp.exit = false;
  temp.collide = true;

  // Update local
  renderAP->updateControl(temp);
  renderAP->createSuperstructure(1000, 10000, 0.1, 10, 1, 0, 0, 0, 0, 100.0, 500.0);

  // Update shared area
  sharedAP->updateControl(renderAP->getControl());
  sharedAP->updateBodies(renderAP->getBodies());
}

// SIM THREAD CALL
// Second thread, concurrent execution of simulation
void startup(shared* sharedAP) {
  // Sim wait control mutex
  std::mutex simWaitMTX;

  // Create access pointer
  simulation* simAP = new simulation;

  // Get new data from shared
  simAP->updateBodies(sharedAP->getBodies());
  simAP->updateControl(sharedAP->getControl());

  while(!simAP->getExit()) {
    // Wait for data change
    std::unique_lock<std::mutex> uniqueSimWaitMTX(simWaitMTX);
    sharedAP->simWait.wait(uniqueSimWaitMTX);

    // Update local control structure
    simAP->updateControl(sharedAP->getControl());

    if(!simAP->getPaused()) {
      // Do itteration
      simAP->itteration();
      // Update shared bodies
      sharedAP->updateBodies(simAP->getBodies());
    } else {
      // Get from shared if paused
      simAP->updateBodies(sharedAP->getBodies());
    }
  }
  // Delete heap objects
  delete simAP;
}
