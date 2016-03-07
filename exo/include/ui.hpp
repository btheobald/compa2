#pragma once
#include <GLFW/glfw3.h>   // GLFW
#include <iostream>
#include <cmath>
#include <GL/glu.h>
#include "AntTweakBar.h"
#include "render.hpp"

// Custom Inputs
bool getMouseHeld(GLFWwindow* window, int button);
void moveCamera(GLFWwindow* window, double cursorX, double cursorY);
void zoomCamera(double change);
void applyCamera(GLFWwindow* window);
void getCoord(GLFWwindow* window, double &aX, double &aY);

// Mouse Callback
void cursorPosCallback(GLFWwindow* window, double cursorX, double cursorY);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

// Window
void windowResizeCallback(GLFWwindow* window, int width, int height);

// Callback Setup
void setCallbacks(GLFWwindow* window);
void setRenderPointer(render* p_renderAP);

// AntTweakBar
class gui {
  private:
    // Windows
    TwBar* simGUI;
    TwBar* bodyGUI;
    TwBar* systemGUI;

    // Sim Control
    double UGC_I = 0;
    double IDT_I = 0;
    int IPF_I = 0;

    // Pause / Run
    bool paused_I = false;
    // Current bodies in simulation
    int numBodies_I = 0;
    // Flag if Collisions should be calculated
    bool doCollisions_I = false;

    // Sim and System gui Setup, Will be called once at start.
    void setupSimGUI();
    void setupSystemGUI();

  public:
    gui(int p_wXRes, int p_wYRes);
    ~gui();

    std::string fileName = "Default.sav";
    // Active Body gui
    int abID_I = 0;
    double abMass_I = 0;
    double abRadius_I = 0;
    double abPositionX_I = 0;
    double abPositionY_I = 0;
    double abVelocityX_I = 0;
    double abVelocityY_I = 0;
    double abForceX_I = 0;
    double abForceY_I = 0;
    double abAccelerationX_I = 0;
    double abAccelerationY_I = 0;
    bool abFixed_I = false;
    float abColor_I[3] = {0.0f, 0.0f, 0.0f};

    // Body gui Setup, Will be called throughout program, handled by Main.
    void setupBodyGUI(int p_abID);

    void updateActiveID(int p_bodyID);
    inline bool getPaused() { return paused_I; };
};

// Class External Callbacks
void TW_CALL saveFileButton(void *cData);
void TW_CALL loadFileButton(void *cData);

// Filename should always have a string and must have a .sav file extension.
void TW_CALL handleFilename(std::string& destinationClientString, const std::string& sourceLibraryString);

void TW_CALL deleteBodyButton(void *cData);
void TW_CALL newBodyButton(void *cData);
void TW_CALL newSuperStructureButton(void *cData);
