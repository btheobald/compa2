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
		glVertex2f(-50.f, -50.f);
		glVertex2f(50.f, -50.f);
		glVertex2f(50.f, 50.f);
		glVertex2f(-50.f, 50.f);
	glEnd();

    TwDraw();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  TwTerminate();
  glfwTerminate();
  return 0;
}