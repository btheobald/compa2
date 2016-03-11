#include "simulation.hpp"
#include <cmath>
#include <iostream>

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
  return std::sqrt(std::abs(p_dX*p_dX) + std::abs(p_dY*p_dY));
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
  double fP = -(lControl.UGC * bA->m * bB->m) / (dV*dV*dV);
  // Component Forces
  double fX = fP * dX;
  double fY = fP * dY;

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
    for(unsigned int y = x+1; y < bodies.size(); y++) {
      // Ignore same body relationship
      //if(x != y) {
      //std::cerr << x << " " << y << std::endl;
      calcAcceleration(bodies[x], bodies[y]);
      //}
    }
  }
}

void simulation::calcAllCollisions(void) {
  for (unsigned int bA = 0; bA < bodies.size(); bA++) {
    for (unsigned int bB = bA+1; bB < bodies.size(); bB++) {
      double xDist = getComponentDistance(bodies[bA], bodies[bB], 0);
      double yDist = getComponentDistance(bodies[bA], bodies[bB], 1);
      double vDist = getVectorDistance(xDist, yDist);

      // TODO: Implement this as an overloaded operator?
      if(bodies[bA]->r+bodies[bB]->r > vDist) {
        // Body A Becomes New Body
        // Add Together Areas
        bodies[bA]->r = sqrt(pow(bodies[bA]->r,2)+pow(bodies[bB]->r,2));

        // Add Together Masses
        double totalMass = bodies[bA]->m + bodies[bB]->m;

        // Get Weighted Mean Position XY
        bodies[bA]->pX = ((bodies[bA]->pX*bodies[bA]->m) + (bodies[bB]->pX*bodies[bB]->m)) / totalMass;
        bodies[bA]->pY = ((bodies[bA]->pY*bodies[bA]->m) + (bodies[bB]->pY*bodies[bB]->m)) / totalMass;

        // Calculate New Velocity through Inelastic Collision (mv+Mv)/(m+M) = v XY
        bodies[bA]->vX = ((bodies[bA]->calcMomentum(0)) + bodies[bB]->calcMomentum(0)) / totalMass;
        bodies[bA]->vY = ((bodies[bA]->calcMomentum(1)) + bodies[bB]->calcMomentum(1)) / totalMass;
        bodies[bA]->m = totalMass;

        // If either body is originally fixed, the resulting body should be fixed.
        if(bodies[bA]->fixed | bodies[bB]->fixed) bodies[bA]->fixed = true;

        // Get average of colours of both bodies
        for(int c = 0; c < 3; c++) {
          bodies[bA]->color[c] = (bodies[bA]->color[c] + bodies[bB]->color[c]) / 2;
        }

        // Delete Body B
        delBody(bB);
      }
    }
  }
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
  // Collisions
  if(lControl.collide)
    calcAllCollisions();
  // Acceleration
  calcAllAcceleration();
  // 1/2 Velocity
  calcAllHalfVelocity();
  // Position
  calcAllPosition();
  // Acceleration
  calcAllAcceleration();
  // 1/2 Velocity
  calcAllHalfVelocity();
}
