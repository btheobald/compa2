#include "body.h"

void calculatePosition(body* bd, float dt) {
  bd->pX += bd->vX * dt;
  bd->pY += bd->vY * dt;
}

void calculateHalfVelocity(body* bd, float dt) {
  bd->vX += 0.5 * bd->aX * dt;
  bd->vY += 0.5 * bd->aY * dt;
}
