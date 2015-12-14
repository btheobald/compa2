// System
#include <GLFW/glfw3.h>
#include <AntTweakBar.h>
#include <iostream>
#include <thread>
using namespace std;

typedef struct {
// Body
	// Body Position
	float positionX = 0;
	float positionY = 0;
	// Body Size
	float width = 0;
	float height = 0;
// Matrix
	// TODO: Implement Matrix Control Variables for Testing
} controlVar;

// Custom
#include "callbacks.h"

void TW_CALL print(void *clientData) {
  cout << "Button Pressed" << endl;
}

static void setupTweakbar() {


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
  TwBar *functionBar;
  functionBar = TwNewBar("Control");

  controlVar variables;
  // Add Variables
  TwAddVarRW(functionBar, "Position X", TW_TYPE_FLOAT, &variables.positionX, NULL);
  TwAddVarRW(functionBar, "Position Y", TW_TYPE_FLOAT, &variables.positionY, NULL);
  TwAddVarRW(functionBar, "Width", TW_TYPE_FLOAT, &variables.width, NULL);
  TwAddVarRW(functionBar, "Height", TW_TYPE_FLOAT, &variables.height, NULL);

  while(!glfwWindowShouldClose(window)) {
	glClearColor(0.1f, 0.1f, 0.1f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Initialize Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 640, 480, 0.0, 1.0, -1.0);

	// Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Render
	glBegin(GL_QUADS);
		glColor3f(0.f, 1.f, 1.f);
		glVertex2f((-(variables.width / 2) + variables.positionX), (-(variables.height / 2) + variables.positionY));
		glVertex2f(( (variables.width / 2) + variables.positionX), (-(variables.height / 2) + variables.positionY));
		glVertex2f(( (variables.width / 2) + variables.positionX), ( (variables.height / 2) + variables.positionY));
		glVertex2f((-(variables.width / 2) + variables.positionX), ( (variables.height / 2) + variables.positionY));
	glEnd();

    TwDraw();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  TwTerminate();
  glfwTerminate();
  return 0;
}