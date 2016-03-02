#include "body.h"

void calculatePosition(body* bd, float dt) {
  bd->pX += bd->vX * dt;
  bd->pY += bd->vY * dt;
}

void calculateVelocity(body* bd, float dt) {
  bd->vX += bd->aX * dt;
  bd->vY += bd->aY * dt;
}
