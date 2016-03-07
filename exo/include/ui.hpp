#pragma once
#include <GLFW/glfw3.h>   // GLFW
#include <iostream>
#include <cmath>
#include <GL/glu.h>
#include "AntTweakBar.h"
#include "render.hpp"
#include "body.hpp"
#include "scenario.hpp"
#include <vector>

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

    // Render Access Pointers
    control* controlPointer;
    std::vector<body*>* bodiesPointer;

    // Sim and System gui Setup, Will be called once at start.
    void setupSimGUI();
    void setupSystemGUI();

  public:
    gui(render* renderAP, int p_wXRes, int p_wYRes);

    void setupBodyGUI(int id);

    std::string fileName = "Default.sav";
};

// Class External Callbacks
void TW_CALL saveFileButton(void *cData);
void TW_CALL loadFileButton(void *cData);

// Filename should always have a string and must have a .sav file extension.
void TW_CALL handleFilename(std::string& destinationClientString, const std::string& sourceLibraryString);

void TW_CALL deleteBodyButton(void *cData);
void TW_CALL newBodyButton(void *cData);
void TW_CALL newSuperStructureButton(void *cData);
