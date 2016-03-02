#include "body.h"

void calculatePosition(body* bd, float dt) {
  bd->pX += bd->vX * dt;
  bd->pY += bd->vY * dt;
}

void calculateHalfVelocity(body* bd, float dt) {
  bd->vX += bd->aX * dt * 0.5;
  bd->vY += bd->aY * dt * 0.5;
}
