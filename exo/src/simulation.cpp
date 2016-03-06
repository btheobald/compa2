#include "simulation.hpp"

double simulation::getComponentDistance(body* bA, body* bB, int xy) {
  if(xy)
    // Y Component
    return bA->pY - bB->pY;
  else
    // X Component
    return bA->pX - bB->pX;
}

double simulation::getVectorDistance(double dX, double dY) {
  // Pythagoras - a^2 + b^2 = c^2
  return std::sqrt(std::abs(dX*dX) + std::abs(dY*dY));
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
  double fP = - (lControl.UGC * bA->m * bB->m) / std::pow(dV, 3);
  // Component Forces
  double fX = fP * dX;
  double fY = fP * dY;

  // a=F/m - Set acceleration to bodies
  // Body A
  bA->aX +=  fX / bA->m;
  bA->aX += -fY / bA->m;
  // Body B
  bB->aX += -fX / bB->m;
  bB->aY +=  fY / bB->m;
}

void simulation::calcAllAcceleration() {

}

void simulation::calcAllCollisions() {

}

void simulation::calcAllHalfVelocity() {

}

void simulation::calcAllPosition() {

}

void simulation::itteration() {

}
