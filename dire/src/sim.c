#include "sim.h"

#include <math.h>
#include <stdint.h>

#include "store.h"

// Distance
float getComponentDistance(body* bA, body* bB, int xy) {
  if(xy)
    return bA->pX - bB->pX;
  else
    return bA->pY - bB->pY;
}

float getVectorDistance(body* bA, body* bB) {
  float dX = getComponentDistance(bA, bB, 0);
  float dY = getComponentDistance(bA, bB, 1);

  return sqrt(dX*dX + dY*dY);
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

  // GmM/r^3
  float fP = (gc * bA->m * bB->m) / (dV*dV*dV);

  // Get component forces
  float fX = fP * getComponentDistance(bA, bB, 0);
  float fY = fP * getComponentDistance(bA, bB, 1);

  // Calculate and set acceleration
  // Body A
  bA->aX =  fX;
  bA->aY = -fY;
  // Body B
  bB->aX = -fX;
  bB->aY =  fY;
}

void itteration(body** bodyArray, int cbc, float gc, float dt) {
  uint8_t** forceMark = genMatrix(cbc);

  int x, y;
  for(x = 0; x < cbc; x++) {
    for(y = x; y < cbc; y++) {
      // Check to calculate acceleration for bodies
      if(checkIfNeeded(forceMark, x, y)) {
        calculateAcceleration(gc, bodyArray[x], bodyArray[y]);
        forceMark[x][y] = 1;
      }
    }
  }
}
