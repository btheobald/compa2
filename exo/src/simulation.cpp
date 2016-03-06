#include "simulation.hpp"
#include <cmath>
#include <iostream>

void startup(shared* sharedAP) {

}

double simulation::getComponentDistance(body* bA, body* bB, int xy) {
  if(xy)
    // Y Component
    return (bA->pY - bB->pY);
  else
    // X Component
    return (bA->pX - bB->pX);
}

double simulation::getVectorDistance(double p_dX, double p_dY) {
  // Pythagoras - a^2 + b^2 = c^2
  return std::sqrt(std::fabs(p_dX*p_dX) + std::fabs(p_dY*p_dY));
}

void simulation::resetAllAcceleration(void) {
  // Reset all body accelerations
  for(unsigned int i = 0; i < bodies.size(); i++) {
    bodies[i]->aX = 0;
    bodies[i]->aY = 0;
  }
}

void simulation::calcAcceleration(body* bA, body* bB) {
  // Calculate and store distances for calculation
  double dX = getComponentDistance(bA, bB, 0);
  double dY = getComponentDistance(bA, bB, 1);
  double dV = getVectorDistance(dX, dY);

  // F=GmM/(r^3) - Pre-component force
  double fP = (lControl.UGC * bA->m * bB->m) / (dV*dV*dV);
  // Component Forces
  double fX = -fP *  dX;
  double fY = -fP *  dY;

  // a=F/m - Set acceleration to bodies
  // Body A
  bA->aX +=  fX / bA->m;
  bA->aY +=  fY / bA->m;
  // Body B
  bB->aX += -fX / bB->m;
  bB->aY += -fY / bB->m;
}

void simulation::calcAllAcceleration(void) {
  resetAllAcceleration(); // Set all accelerations to 0;
  for(unsigned int x = 0; x < bodies.size(); x++) {
    // Evaluate bottom left of calculation matrix
    for(unsigned int y = x; y < bodies.size(); y++) {
      // Ignore same body relationship
      if(x != y) {
        calcAcceleration(bodies[x], bodies[y]);
      }
    }
  }
}

void simulation::calcAllCollisions(void) {
  // TODO: implement collisions
}

void simulation::calcAllHalfVelocity(void) {
  for(unsigned int i = 0; i < bodies.size(); i++) {
    bodies[i]->calcHalfVelocity(lControl.IDT);
  }
}

void simulation::calcAllPosition(void) {
  for(unsigned int i = 0; i < bodies.size(); i++) {
    bodies[i]->calcPosition(lControl.IDT);
    //std::cout << bodies[i]->pX << " " << bodies[i]->pY << " ";
  }
  //std::cout << std::endl;
}

void simulation::itteration(void) {
  // 1/2 Velocity
  calcAllHalfVelocity();
  // Position
  calcAllPosition();
  // Collisions
  calcAllCollisions();
  // Acceleration
  calcAllAcceleration();
  // 1/2 Velocity
  calcAllHalfVelocity();
}
