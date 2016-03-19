// Standard library includes
#include <iostream>
#include <thread>
// External library includes
#include <GLFW/glfw3.h>
#include <AntTweakBar.h>
// Custom header includes
#include "shared.hpp"
#include "simulation.hpp"
#include "render.hpp"
#include "body.hpp"
#include "ui.hpp"

// Sim thread startup function
void startup(shared* sharedAP);
// GLFW and OpenGL startup Functions
void initDisplay(int lXRes, int lYRes);
GLFWwindow* windowSetup(void);
// Default Scenario startup
void setupDefaultScenario(render* renderAP, shared* sharedAP);

int main(void) {
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
    applyCamera();

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

  #ifdef EXITNOTE
    std::cerr << "Main Exit" << std::endl;
  #endif

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

  #ifdef C_UGC
    temp.UGC = C_UGC;
  #endif
  #ifdef C_IDT
    temp.IDT = C_IDT;
  #endif
  #ifdef C_PAUSED
    temp.paused = C_PAUSED;
  #endif
  #ifdef C_COLLIDE
    temp.collide = C_COLLIDE;
  #endif

  // Update local
  renderAP->updateControl(temp);
  #ifdef DEFAULT
    float cWhite[3] = { 1.0f, 1.0f, 1.0f };
    renderAP->createSuperstructure(100, 10000, 0.1, 5, 0.1, 0, 0, 0, 0, 20.0, 200.0, cWhite);
  #endif

  // Default Scenario - Compile-Time Selection CS=-DTSx
  #ifdef TS1
    renderAP->addBody(new body(1, 1, 0, 0, 0, 0));
  #endif
  #ifdef TS2
    renderAP->addBody(new body(1000, 10, 0, 0, 0, 0));
    renderAP->addBody(new body(0.1, 1, 100, 0, 0, 1.00005));
  #endif
  #ifdef TS3
    renderAP->addBody(new body(1, 1, 10, 0, 0, 0));
    renderAP->addBody(new body(1, 1, -10, 0, 0, 0));
  #endif
  #ifdef TS4
    float cWhite[3] = { 1.0f, 1.0f, 1.0f };
    renderAP->createSuperstructure(TS4BODIES, 10000, 0.1, 10, 0.1, 0, 0, 0, 0, 50.0, 1000.0, cWhite);
  #endif
  #ifdef TS5
    renderAP->addBody(new body(1, 1, 9.99E15, 0, 1E5, 0));
  #endif
  #ifdef TS6
    renderAP->addBody(new body(1, 1, -9.99E15, 0, 3E9, 0));
  #endif
  #ifdef TS7
    // Body Reference Grid
    renderAP->addBody(new body(0.001, 1,  10,   0, true));
    renderAP->addBody(new body(0.001, 1, -10,   0, true));
    renderAP->addBody(new body(0.001, 1,   0,  10, true));
    renderAP->addBody(new body(0.001, 1,   0, -10, true));
    renderAP->addBody(new body(0.001, 1, -10, -10, true));
    renderAP->addBody(new body(0.001, 1,  10, -10, true));
    renderAP->addBody(new body(0.001, 1, -10,  10, true));
    renderAP->addBody(new body(0.001, 1,  10,  10, true));
    renderAP->addBody(new body(0.001, 1, 100,   0, true));
    renderAP->addBody(new body(0.001, 1,-100,   0, true));
    renderAP->addBody(new body(0.001, 1,   0, 100, true));
    renderAP->addBody(new body(0.001, 1,   0,-100, true));
    renderAP->addBody(new body(0.001, 1,-100,-100, true));
    renderAP->addBody(new body(0.001, 1, 100,-100, true));
    renderAP->addBody(new body(0.001, 1,-100, 100, true));
    renderAP->addBody(new body(0.001, 1, 100, 100, true));
    renderAP->addBody(new body(0.001, 1, 1E5,   0, true));
    renderAP->addBody(new body(0.001, 1, 1E6,   0, true));
    renderAP->addBody(new body(0.001, 1, 1E7,   0, true));
    renderAP->addBody(new body(0.001, 1, 1E8,   0, true));
  #endif
  #ifdef TS8
    renderAP->addBody(new body(10000, 10,   0,    0,  0,      0));
    renderAP->addBody(new body(1,     1,    1000, 0,  0,      1.00005));
    renderAP->addBody(new body(0.01,  0.01, 1000, 10, 0.1005, 1.00005));
  #endif
  #ifdef TS9
    renderAP->addBody(new body(100, 1, 0, 0, true));
    renderAP->addBody(new body(1, 1, 10, 0, 0, 1));
  #endif
  #ifdef TS10
    float cWhite[3] = { 1.0f, 1.0f, 1.0f };
    renderAP->createSuperstructure(1, 10000, 0.1, 5, 0.1, 0, 0, 0, 0, 100.0, 100.001, cWhite);
  #endif
  #ifdef TS11
    renderAP->addBody(new body(1, 1, 0, 0, 0, 0));
    renderAP->addBody(new body(1, 1, 10, 0, 0, 0.11));
    renderAP->addBody(new body(1, 1, -10, 0, 0, -0.11));
  #endif
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

  bool initCalc = true;
  int iCount = 0;

  #ifdef SP
    while((!simAP->getExit()) & (iCount < SIMITRS)) {
  #endif
  #ifndef SP
  while(!simAP->getExit())     {
  #endif

    #ifndef NOSYNC
    // Wait for data change - Thread Sync
    std::unique_lock<std::mutex> uniqueSimWaitMTX(simWaitMTX);
    sharedAP->simWait.wait(uniqueSimWaitMTX);
    #endif

    // Update local control structure
    simAP->updateControl(sharedAP->getControl());

    if(!simAP->getPaused()) {
      if(initCalc) {
        // Do initial calculations.
        simAP->initialCalc();
        initCalc = false;
      }
      for(int iter = 0; iter < simAP->getIPF(); iter++) {
        // Do itteration
        simAP->iteration();
        iCount++;

        #ifdef SIPF
          std::cerr << "i";
        #endif

        // Break out of ipf loop if paused or exit.
        if(sharedAP->getPaused() | sharedAP->getExit()) break;
      }

      #ifdef SIPF
        std::cerr << std::endl;
      #endif

      // Update shared bodies
      sharedAP->updateBodies(simAP->getBodies());
    } else {

      #ifdef SCI
        std::cerr << "Current Iteration: " << iCount << std::endl;
      #endif

      // Get from shared if paused
      simAP->updateBodies(sharedAP->getBodies());
      // Request recalculation of initial calculations once unpaused.
      initCalc = true;
    }
  }
  // Directly unset shared exit variable to confirm sim exit.
  sharedAP->setExit(0);

  #ifdef EXITNOTE
    std::cerr << "Simulation Thread Exit" << std::endl;
  #endif
}
