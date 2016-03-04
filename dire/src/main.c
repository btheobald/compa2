#include <stdio.h>
#include <stdlib.h>

#include "store.h"
#include "body.h"
#include "sim.h"

int main() {
  body** bStore = allocateBodyArray(2);
  bStore[0] = malloc(sizeof(body));
  bStore[1] = malloc(sizeof(body));
  bStore[2] = malloc(sizeof(body));

  bStore[0]->m = 1000;
  bStore[0]->pX = 0;
  bStore[0]->pY = 0;
  bStore[0]->vX = 0;
  bStore[0]->vY = 0;

  bStore[1]->m = 1;
  bStore[1]->pX = 100;
  bStore[1]->pY = 0;
  bStore[1]->vX = 0;
  bStore[1]->vY = 3.164;

  bStore[2]->m = 10;
  bStore[2]->pX = 1000;
  bStore[2]->pY = 0;
  bStore[2]->vX = 0;
  bStore[2]->vY = 0.5;

  for(int i = 0; i < 10000000; i++) {
    itteration(bStore, 3, 1, 0.1);
  }

  freeBodyArray(bStore, 3);

  return 0;
}
