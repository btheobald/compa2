#include "render.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <random>

void render::drawBody(body* p_b) {
  const int segments = 64;

  double posX = p_b->pX;
  double posY = p_b->pY;
  double radius = p_b->r;

  // Precalc
  float theta = 2 * M_PI / segments;

  // Factors
  float tanFact = tan(theta);
  float radFact = cos(theta);

  float x = radius;
  float y = 0;

  // Plot Minimum Point.
  glBegin(GL_POINTS);
    glVertex2f(posX, posY);
  glEnd();

  // Plot Real Size
  glBegin(GL_POLYGON);
    for(int i = 0; i < segments; i++) {
      // Output Vertex
      glVertex2f(x + posX, y + posY);

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

void render::createSuperstructure(int p_soBodies, double p_cMass, double p_oMass, double p_cRadius, double p_oRadius, double p_cPosX, double p_cPosY, double p_cVelX, double p_cVelY, double p_coSpacing, double p_sRadius) {
  // Create a Pseudo-random circular distribution of bodies around a central body.

  // Use Mersenne Twister for RNE within range.
  std::uniform_real_distribution<> pos(0, p_sRadius*2);
   // Use random device for seed value
  std::random_device r;
  std::mt19937 gen(r());
  //std::mt19937 gen;

  // Temporary Variables
  double tempRand, tempCirX, tempCirY, tempDist, tempVelX, tempVelY;
  // Add Central Body
  addBody(new body(p_cMass, p_cRadius, p_cPosX, p_cPosY, p_cVelX, p_cVelY));
  //int bodyOffset = bodyStore.size() - 1;
  for(int bIDC = 0; bIDC < p_soBodies; bIDC++) {
    // Ensure that bodies are not too close to center.
    do {
      tempRand = pos(gen) - p_sRadius;
    } while((tempRand < p_coSpacing) & (tempRand > -p_coSpacing));
    // Map to Circle
    tempCirX = p_cPosX+(tempRand * std::cos(2 * M_PI * tempRand));
    tempCirY = p_cPosY+(tempRand * std::sin(2 * M_PI * tempRand));

    // Calculate Distance to Body
    tempDist = std::sqrt(std::pow(p_cPosX-tempCirX,2) + std::pow(p_cPosY-tempCirY,2));

    // Calc Velocity
    tempVelX = copysign(std::sqrt((lControl.UGC*(p_cMass+p_oMass)) / std::pow(tempDist,3)) * (tempCirY-p_cPosY), (tempCirY-p_cPosY)) + p_cVelX;
    tempVelY = copysign(std::sqrt((lControl.UGC*(p_cMass+p_oMass)) / std::pow(tempDist,3)) * (tempCirX-p_cPosX), -(tempCirX-p_cPosX)) + p_cVelY;

    addBody(new body(p_oMass, p_oRadius, tempCirX, tempCirY, tempVelX, tempVelY));
  }
}

void render::drawScene(void) {
  for(unsigned int i = 0; i < bodies.size(); i++) {
    drawBody(bodies[i]);
  }
}

int render::checkCoord(double x, double y, double ad) {
  for(unsigned int i = 0; i < bodies.size(); i++) {
    if((x < bodies[i]->pX + (bodies[i]->r + ad))  &
       (x > bodies[i]->pX - (bodies[i]->r + ad))  &
       (y < bodies[i]->pY + (bodies[i]->r + ad))  &
       (y > bodies[i]->pY - (bodies[i]->r + ad))) {
      return i;
    }
  }
  return -1;
}
