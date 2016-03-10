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
#include "body.hpp"
#include "ui.hpp"

// Sim thread startup function
void startup(shared* sharedAP);
// GLFW and OpenGL startup Functions
void initDisplay(int lXRes, int lYRes);
GLFWwindow* windowSetup();
// Default Scenario startup
void setupDefaultScenario(render* renderAP, shared* sharedAP);

int main() {
  // Setup window and give pointer
  GLFWwindow* window = windowSetup();

  // Create objects
  render renderMain;
  shared sharedMain;

  // Create access pointers
  render* renderAP = &renderMain;
  shared* sharedAP = &sharedMain;

  setupDefaultScenario(renderAP, sharedAP);

  setupGUI(window, renderAP);

  // Create simulation thread
  std::thread simThread(startup, sharedAP);

  // Main Runtime Loop
  while(!glfwWindowShouldClose(window)) {
    // Clear screen before drawing
    glClear(GL_COLOR_BUFFER_BIT);

    sharedAP->updateControl(renderAP->getControl());

    if(renderAP->getPaused()) {
      updateBody(renderAP); // Update body storage from interface
      // Send update to shared
      sharedAP->updateBodies(renderAP->getBodies());
    } else {
      updateUI(renderAP); // Update interface from body store
      // Get update from shared
      renderAP->updateBodies(sharedAP->getBodies());
    }

    // Wake sim thread
    sharedAP->simWait.notify_all();

    // Render scene
    renderAP->drawScene();

    // Apply camera transform and scale
    applyCamera(window);

    // Draw GUI
    TwDraw();

    // Display is double buffered to prevent screen tearing
    // Swap display buffers
    glfwSwapBuffers(window);
    // Poll and process events
    glfwPollEvents();
  }

  // Unpause and Exit, direct to shared
  sharedAP->setPaused(0);
  sharedAP->setExit(1);

  // Repeat sim wait notify until exit is acknowleged, directly check shared
  while(sharedAP->getExit()) {
    sharedAP->simWait.notify_all();
  }

  // Program exit
  simThread.join();

  // Terminate Libraries
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

void initDisplay(int lXRes, int lYRes) {
  // Init Projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-lXRes, lXRes, -lYRes, lYRes, 1.0f, -1.0f);

  // Init Modelview
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Set Viewport Extents
  glViewport(0, 0, lXRes, lYRes);
  glClearColor(0.0f, 0.0f, 0.0f, 1);
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
  renderAP->createSuperstructure(1000, 10000, 0.1, 10, 1, 0, 0, 0, 0, 50.0, 500.0);

  // Update shared area
  sharedAP->updateControl(renderAP->getControl());
  sharedAP->updateBodies(renderAP->getBodies());
}

// SIM THREAD CALL
// Second thread, concurrent execution of simulation
void startup(shared* sharedAP) {
  // Sim wait control mutex
  std::mutex simWaitMTX;

  // Create sim object
  simulation simMain;

  // Create access pointer
  simulation* simAP = &simMain;

  // Get new data from shared
  simAP->updateBodies(sharedAP->getBodies());
  simAP->updateControl(sharedAP->getControl());

  while(!simAP->getExit()) {
    // Wait for data change - Thread Sync
    std::unique_lock<std::mutex> uniqueSimWaitMTX(simWaitMTX);
    sharedAP->simWait.wait(uniqueSimWaitMTX);

    // Update local control structure
    simAP->updateControl(sharedAP->getControl());

    if(!simAP->getPaused()) {
      for(int iter = 0; iter < simAP->getIPF(); iter++) {
        // Do itteration
        simAP->itteration();
        // Break out of ipf loop if paused or exit.
        if(sharedAP->getPaused() | sharedAP->getExit()) break;
      }

      // Update shared bodies
      sharedAP->updateBodies(simAP->getBodies());
    } else {
      // Get from shared if paused
      simAP->updateBodies(sharedAP->getBodies());
    }
  }
  // Directly unset shared exit variable to confirm sim exit.
  sharedAP->setExit(0);
}
