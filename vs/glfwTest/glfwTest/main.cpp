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
  int windowX = 960;
  int windowY = 480;

  // Body
  float positionX = 300;
  float positionY = 100;
  float width = 100;
  float height = 100;
  // Ortho Matrix
  float left = 0.0f;
  float right = (float)windowX;
  float bottom = (float)windowY; 
  float top = 0.0f;
  float near = 1.0f;
  float far = -1.0f;

  GLFWwindow* window;

  // Init GLFW
  glfwInit();
  window = glfwCreateWindow(windowX, windowY, "Test Window", NULL, NULL);
  glfwMakeContextCurrent(window);

  setCallbacks(window);

  // Init AntTweakBar
  TwInit(TW_OPENGL, NULL);
  TwWindowSize(windowX, windowY);

  // Create Tweak Bar
  TwBar *functionBar;
  functionBar = TwNewBar("Control");

  // Add Variables
  TwAddSeparator(functionBar, "Body", NULL);
  TwAddVarRW(functionBar, "Position X", TW_TYPE_FLOAT, &positionX, NULL);
  TwAddVarRW(functionBar, "Position Y", TW_TYPE_FLOAT, &positionY, NULL);
  TwAddVarRW(functionBar, "Width", TW_TYPE_FLOAT, &width, NULL);
  TwAddVarRW(functionBar, "Height", TW_TYPE_FLOAT, &height, NULL);

  TwAddSeparator(functionBar, "Ortho Matrix", NULL);
  TwAddVarRW(functionBar, "Left", TW_TYPE_FLOAT, &left, NULL);
  TwAddVarRW(functionBar, "Right", TW_TYPE_FLOAT, &right, NULL);
  TwAddVarRW(functionBar, "Bottom", TW_TYPE_FLOAT, &bottom, NULL);
  TwAddVarRW(functionBar, "Top", TW_TYPE_FLOAT, &top, NULL);
  TwAddVarRW(functionBar, "Near", TW_TYPE_FLOAT, &near, NULL);
  TwAddVarRW(functionBar, "Far", TW_TYPE_FLOAT, &far, NULL);

  while(!glfwWindowShouldClose(window)) {
	glClearColor(0.1f, 0.1f, 0.1f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Initialize Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0, windowX, windowY, 0.0, 1.0, -1.0);
  glOrtho(left, right, bottom, top, near, far);

	// Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Render
	glBegin(GL_QUADS);
		glColor3f(0.f, 1.f, 1.f);
		glVertex2f((-(width / 2) + positionX), (-(height / 2) + positionY));
		glVertex2f(( (width / 2) + positionX), (-(height / 2) + positionY));
		glVertex2f(( (width / 2) + positionX), ( (height / 2) + positionY));
		glVertex2f((-(width / 2) + positionX), ( (height / 2) + positionY));
	glEnd();

    TwDraw();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  TwTerminate();
  glfwTerminate();
  return 0;
}