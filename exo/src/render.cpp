#include "render.hpp"
#include <GLFW/glfw3.h>

void render::drawBody(body* p_b) {
  glPointSize(2);
  glBegin(GL_POINTS);
    glVertex2f(p_b->pX, p_b->pY);
  glEnd();
}

void render::applyCamera(void) {

}

void render::createSuperstructure() {

}

void render::drawScene(void) {
  for(unsigned int i = 0; i < bodies.size(); i++) {
    drawBody(bodies[i]);
  }
}
