#include "store.h"

#include <stdio.h>
#include <stdlib.h>

// Body array management functions
body** allocateBodyArray(int cbc) {
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

// Calculation marking matrix
uint8_t** genMatrix(int squareSize) {
  uint8_t** matrixPtr;

  // Allocate Memory
  matrixPtr = malloc(sizeof(uint8_t *) * squareSize);
  for(int x = 0; x < squareSize; x++) {
    matrixPtr[x] = malloc(sizeof(uint8_t) * squareSize);
  }

  resetMatrix(matrixPtr, squareSize);

  return matrixPtr;
}

// Set default state
void resetMatrix(uint8_t** matrixPtr, int cbc) {
  // Populate Matrix
  for(int x = 0; x < cbc; x++) {
    for(int y = 0; y < cbc; y++) {
      if(x == y)
        // Set 'same' to invalid
        matrixPtr[x][y] = 2;
      else
        matrixPtr[x][y] = 0;

      printf("%d ", matrixPtr[x][y]);
    }
    printf("\n");
  }
}
