#include <stdio.h>
#include <stdlib.h>

#include "store.h"
#include "body.h"
#include "sim.h"

int main() {
  body** bStore = allocateBodyArray(2);
  bStore[0] = malloc(sizeof(body));
  bStore[1] = malloc(sizeof(body));

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

  for(int i = 0; i < 2000; i++) {
    itteration(bStore, 2, 1, 0.1);
  }

  freeBodyArray(bStore, 2);

  return 0;
}
