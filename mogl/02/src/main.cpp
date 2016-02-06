// Standard Library
#include <iostream>
#include <cstdlib>

// External Libary
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

#include "shader.hpp"

void initWindow(GLFWwindow* &window, int windowX, int windowY, const char* title);

// Vertex Buffer Data
static const GLfloat g_vertex_buffer_data[] = {
  -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

int main() {
  GLFWwindow* mainWindow;
  initWindow(mainWindow, 640, 480, "Test Window");

  // Create VAO and Set as Current
  GLuint vertexArrayID;
  glGenVertexArrays(1, &vertexArrayID);
  glBindVertexArray(vertexArrayID);

  // Vertex Buffer
  GLuint vertexBuffer;
  // Generate a Buffer, add to VB.
  glGenBuffers(1, &vertexBuffer);
  // Bind Vertex Array Buffer
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  // Send Vertex Data
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  // Create and Compile GLSL Shaders
  GLuint programID = loadShaders("shader/vertex.glsl", "shader/fragment.glsl");
  // Use Shader Program
  glUseProgram(programID);

  while(!glfwWindowShouldClose(mainWindow)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render Here
    // Enable Vertex Array 0
    glEnableVertexAttribArray(0);
    // Bind Vertex Array Buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // Sets VB Pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Draw Triangle, Vertex 0-3
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // Disable Vertex Array 0
    glDisableVertexAttribArray(0);

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
