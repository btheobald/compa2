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

// Sim thread startup function
void startup(shared* sharedAP);

int main() {
    /*                       */
   // GLFW Init Boilerplate //
  /*                       */
  if(!glfwInit()) {
    // Exit if GLFW does not init
    std::cerr << "GLFW could not init" << std::endl;
    return 1;
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
    return 1;
  }

  glfwMakeContextCurrent(window);
  initDisplay(wXRes, wYRes);
    /*                       */
   // GLFW Boilerplate End  //
  /*                       */

  // Create access pointers
  render* renderAP = new render;
  shared* sharedAP = new shared;

  // Precessing Orbits
  //renderAP->addBody(new body(10000, 10,  100, 0, 0,  1.6));
  //renderAP->addBody(new body(10000, 10, -100, 0, 0, -1.6));

  //renderAP->addBody(new body(1000, 10, 0, 0, 0, 0));
  //renderAP->addBody(new body(0.1, 1, 500, 0, 0, 0.44));
  //renderAP->addBody(new body(0.001, 0.5, 500, 10, 0.0317, 0.44));

  renderAP->createSuperstructure(1000, 1000, 0.01, 10, 1, 0, 0, 0, 0, 100.0, 150.0);
  //renderAP->addBody(new body(10, 1, 0, 0, true));
  //renderAP->addBody(new body(1, 1, 100, 0, 0, 0.105));

  // Update shared area
  sharedAP->updateBodies(renderAP->getBodies());

  // Create simulation thread
  std::thread simThread(startup, sharedAP);

  // Main Runtime Loop
  while(!glfwWindowShouldClose(window)) {
    // Clear screen before drawing
    glClear(GL_COLOR_BUFFER_BIT);

    // Get update from shared
    //std::cerr << "render from shared" << std::endl;
    renderAP->updateBodies(sharedAP->getBodies());
    sharedAP->simWait.notify_all();
    // Render Scene
    renderAP->drawScene();
    // Display is double buffered to prevent screen tearing
    // Swap display buffers
    glfwSwapBuffers(window);
    // Poll and process events
    glfwPollEvents();
  }

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

// Second thread, concurrent execution of simulation
void startup(shared* sharedAP) {
  // Sim Wait Control Mutex
  std::mutex simWaitMTX;

  // Create access pointer
  simulation* simAP = new simulation;

  // Get new data from shared
  simAP->updateBodies(sharedAP->getBodies());

  //while(1) {
  for(int i = 0; i < 60; i++) {
    //if(sharedAP->getTaken()) {
      //std::cerr << "itteration" << std::endl;
      simAP->itteration();
      sharedAP->updateBodies(simAP->getBodies());

      // Wait for data change
      std::unique_lock<std::mutex> uniqueSimWaitMTX(simWaitMTX);
      sharedAP->simWait.wait(uniqueSimWaitMTX);
    //}
  }
  std::cerr << "Sim Exit" << std::endl;
  // Delete heap objects
  delete simAP;
}
