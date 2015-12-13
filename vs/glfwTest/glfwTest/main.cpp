// System
#include <GLFW/glfw3.h>
#include <AntTweakBar.h>
#include <iostream>
#include <thread>
using namespace std;

// Custom
#include "callbacks.h"

void TW_CALL print(void *clientData) {
  cout << "Button Pressed" << endl;
}

int main() {
  GLFWwindow* window;

  // Init GLFW
  glfwInit();
  window = glfwCreateWindow(640, 480, "Test Window", NULL, NULL);
  glfwMakeContextCurrent(window);

  setCallbacks(window);

  // Init AntTweakBar
  TwInit(TW_OPENGL, NULL);
  TwWindowSize(640, 480);

  // Create Tweak Bar
  TwBar *testBar;
  testBar = TwNewBar("Test Tweak Bar");
  TwAddButton(testBar, "Output", print, NULL, NULL);

  while(!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_CLEAR_VALUE);
    // Render
    TwDraw();
    
    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}