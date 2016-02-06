// Standard Library
#include <iostream>
#include <cstdlib>

// External Libary
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

void initWindow(GLFWwindow* &window, int windowX, int windowY, const char* title);

int main() {
  GLFWwindow* mainWindow;
  initWindow(mainWindow, 640, 480, "Test Window");

  while(!glfwWindowShouldClose(mainWindow)) {
    // Render Here

    // Swap Buffers
    glfwSwapBuffers(mainWindow);
    // Poll Events
    glfwPollEvents();
  }
}

void initWindow(GLFWwindow* &window, int windowX, int windowY, const char* title) {
  if(!glfwInit()) {
    std::cerr << "GLFW Init Failed" << std::endl;
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_SAMPLES, 8); // MSAA x8
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 3.3
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // or Higher
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // New OpenGL

  window = glfwCreateWindow(windowX, windowY, title, NULL, NULL);

  if(window == NULL) {
    std::cerr << "GLFW Window Open Failed." << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  glewExperimental = true;

  if(glewInit() != GLEW_OK) {
    std::cerr << "GLEW Init Failed" << std::endl;
    exit(EXIT_FAILURE);
  }
}
