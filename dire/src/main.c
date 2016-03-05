#include <stdio.h>
#include <stdlib.h>

#include "store.h"
#include "body.h"
#include "sim.h"

const int bodyCount = 3;

int main() {
  body** bStore = allocateBodyArray(bodyCount);

  bStore[0] = createBody(1000, 0, 0, 0, 0);
  bStore[1] = createBody(1, 10, 0, 0, 10);
  bStore[2] = createBody(1, 20, 0, 0, 7.071);

  for (int i = 0; i < 1000; i++) {
    itteration(bStore, bodyCount, 1, 0.01);
  }

  freeBodyArray(bStore, bodyCount);

  return 0;
}
