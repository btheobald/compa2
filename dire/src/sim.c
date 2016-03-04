#include "sim.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#include "store.h"

// Distance
float getComponentDistance(body* bA, body* bB, int xy) {
  if(xy)
    return bA->pY - bB->pY;
  else
    return bA->pX - bB->pX;
}

float getVectorDistance(body* bA, body* bB) {
  float dX = getComponentDistance(bA, bB, 0);
  float dY = getComponentDistance(bA, bB, 1);

  return sqrt(fabsf(dX*dX) + fabsf(dY*dY));
}

// Calculate Forces
int checkIfNeeded(uint8_t** forceMark, int bA, int bB) {
  // False if same body compared
  if(bA == bB) return 0;
  // False if marked done
  if(forceMark[bA][bB] == 1) return 0;
  // False if marked invalid
  if(forceMark[bA][bB] == 2) return 0;

  return 1;
}

void calculateAcceleration(float gc, body* bA, body* bB) {
  float dV = getVectorDistance(bA, bB);

  // GmM/(r^3)
  float fP = (gc * bA->m * bB->m) / (dV*dV*dV);

  // Get component forces
  float fX = -fP * getComponentDistance(bA, bB, 0);
  float fY = -fP * getComponentDistance(bB, bA, 1);

  // Calculate and set acceleration
  // Body A
  bA->aX +=  fX / bA->m;
  bA->aY += -fY / bA->m;
  // Body B
  bB->aX += -fX / bB->m;
  bB->aY +=  fY / bB->m;
}

void resetAcceleration(body** bodyStore, float cbc) {
  for(int i = 0; i < cbc; i++) {
    bodyStore[i]->aX = 0;
    bodyStore[i]->aY = 0;
  }
}

void itteration(body** bodyArray, int cbc, float gc, float dt) {
  uint8_t** forceMark = genMatrix(cbc);

  // 1/2 Velocity
  for(int bc = 0; bc < cbc; bc++) {
    calculateHalfVelocity(bodyArray[bc], dt);
    printf("%f %f ", bodyArray[bc]->pX, bodyArray[bc]->pY);
  }
  printf("\n");

  // Position
  for(int bc = 0; bc < cbc; bc++) {
    calculatePosition(bodyArray[bc], dt);
  }

  // Acceleration
  resetAcceleration(bodyArray, cbc);
  for(int x = 0; x < cbc; x++) {
    for(int y = x; y < cbc; y++) {
      // Check to calculate acceleration for bodies
      if(checkIfNeeded(forceMark, x, y)) {
        calculateAcceleration(gc, bodyArray[x], bodyArray[y]);
        forceMark[x][y] = 1;
      }
    }
  }

  // 1/2 Velocity
  for(int bc = 0; bc < cbc; bc++) {
    calculateHalfVelocity(bodyArray[bc], dt);
  }

  freeMatrix(forceMark, cbc);
}
