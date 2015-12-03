#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>

using namespace std;

static void error_callback(int error, const char* description)
{
    cerr << description << endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void glDrawCircle(float cx, float cy, float r, int segments) {
  float theta = 2 * 3.1415926 / float(segments);
  // Factors
  float tanFact = tan(theta);
  float radFact = cos(theta);
  
  float x = r;
  float y = 0;
  
  glBegin(GL_POLYGON);
  for(int i = 0; i < segments; i++) {
    // Output Vertex
    glVertex2f(x + cy, y + cy);
    
    // Copy previous coordinates
    float lx = -y;
    float ly =  x;
    
    // Calculate Next Vertex
    x += lx * tanFact;
    y += ly * tanFact;
    
    x *= radFact;
    y *= radFact;
  }
  glEnd();
}

int main() {
  if (!glfwInit()) {
    return 1;
  }
  
  GLFWwindow* window = glfwCreateWindow(640, 480, "Test", NULL, NULL);
  
  glfwSetErrorCallback(error_callback);
  
  if (!window) {
    glfwTerminate();
    return 1;
  }
  
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);
  
  glfwSetKeyCallback(window, key_callback);
  
  while (!glfwWindowShouldClose(window)) {
    float ratio;
    int width, height;
    
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height;
    
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    
    glDrawCircle(300, 150, 100, 64);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  glfwDestroyWindow(window);
  glfwTerminate();
  
  return 0;
}
