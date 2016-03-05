#include "body.h"

#include <stdlib.h>

void calculatePosition(body* bd, float dt) {
  bd->pX += bd->vX * dt;
  bd->pY += bd->vY * dt;
}

void calculateHalfVelocity(body* bd, float dt) {
  bd->vX += 0.5 * bd->aX * dt;
  bd->vY += 0.5 * bd->aY * dt;
}

body* createBody(float m, float pX, float pY, float vX, float vY) {
  // Create allocation pointer
  body* b;

  // Allocate memory
  b = malloc(sizeof(body));

  // Assign attributes
  b->m = m;
  b->pX = pX;
  b->pY = pY;
  b->vX = vX;
  b->vY = vY;

  // Return pointer to memory
  return b;
}
