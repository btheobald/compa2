#include <stdio.h>
#include <stdlib.h>

#include "store.h"
#include "body.h"
#include "sim.h"

int main() {
  body** bStore = allocateBodyArray(2);
  bStore[0] = malloc(sizeof(body));
  bStore[1] = malloc(sizeof(body));

  freeBodyArray(bStore, 2);

  return 0;
}
