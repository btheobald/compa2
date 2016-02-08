#pragma once
#include <GLFW/glfw3.h>   // GLFW
#include <iostream>
#include <cmath>
#include <GL/glu.h>
#include <AntTweakBar.h>  // AntTweakBar

class interface {
private:
  // Camera Variables
  //  World Position
  double cameraPosX, cameraPosY;
  // Movement Factor
  double moveFact;
  // Zoom Scale Factor
  double scaleFact;

  // Mouse Variables
  double winX, winY;
  double prevWinX, prevWinY;
  double actX, actY;

  // Screen
  int resX, resY;

  // Check if mouse is held
  bool getMouseHeld(GLFWwindow* window, int button);
  // Calculate drag vector and add to transform total

  void updateMouseActual();
  // Callbacks
  // Checks for position of cursor for camera movement
  void cursorPos(GLFWwindow* window);
  // Checks for a right mouse button click for body selection
  void mouseButton(GLFWwindow* window);
  // Checks for scroll wheel movement for zoom
  void mouseScroll(GLFWwindow* window);
  // Checks for arrow keys for camera movement / zoom
  void keyboardKey(GLFWwindow* window);
  void keyboardChar(GLFWwindow* window);
  // Resets GLOrtho on window resize, also sets ATB window size and maintains camera
  void windowResize(GLFWwindow* window);

public:
  // Constructor sets callbacks
  interface(GLFWwindow* window);
  ~interface();

  // Set Camera XY
  //void setCameraPos(int xyIndex);
  //void setCameraScale(double p_Scale);

  // Update All Inputs
  void inputLoop(GLFWwindow* window);

  void performOperations();
};
