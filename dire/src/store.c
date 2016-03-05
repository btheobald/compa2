#include "store.h"

#include <stdio.h>
#include <stdlib.h>

// Body array management functions
body** allocateBodyArray(int cbc) {
  // Create allocation pointer
  body** arrayBase;

  // Allocate Memory
  arrayBase = malloc(sizeof(body *) * cbc);

  return arrayBase;
}

int freeBodyArray(body** arrayBase, int cbc) {
  for(int i = 0; i < cbc; i++) {
    free(arrayBase[i]); // Free body at location
  }
  free(arrayBase); // Free Array
  return 1;
}
