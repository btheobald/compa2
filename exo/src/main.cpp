// Program Includes
#include "shared.hpp"
#include "simulation.hpp"
#include "render.hpp"

// Standard Library
#include <iostream>
#include <thread>
// External Libraries
#include <GLFW/glfw3.h>
#include <AntTweakBar.h>

// Sim thread startup function
void startup(shared* sharedAP);

int main() {
    /*                       */
   // GLFW Init Boilerplate //
  /*                       */
  if(!glfwInit()) {
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
    std::cerr << "GLFW could not create window" << std::endl;
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);
    /*                       */
   // GLFW Boilerplate End  //
  /*                       */

  // Create access pointers
  render* renderAP = new render;
  shared* sharedAP = new shared;

  sharedAP->updateBodies(renderAP->getBodies());

  // Create simulation thread
  std::thread simThread(startup, sharedAP);

  // Main Runtime Loop
  while(!glfwWindowShouldClose(window)) {


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
  glfwTerminate();

  return 0;
}

// Second thread, concurrent execution of simulation
void startup(shared* sharedAP) {
  simulation* simAP = new simulation;

  simAP->updateBodies(sharedAP->getBodies());

  delete simAP;
}
