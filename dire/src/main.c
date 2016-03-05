#include <stdio.h>
#include <stdlib.h>

#include "store.h"
#include "body.h"
#include "sim.h"

int main() {
  body** bStore = allocateBodyArray(10000);

  printf("%d \n", (int)sizeof(body));

  int c = 0;
  for (int x = 0; x < 100; x++) {
    for (int y = 0; y < 100; y++) {
      bStore[c] = createBody(1, x, y, 0, 0);
      c++;
    }
  }

  for (int i = 0; i < 1; i++) {
    itteration(bStore, 10000, 1, 0.1);
  }

  freeBodyArray(bStore, 10000);

  return 0;
}
