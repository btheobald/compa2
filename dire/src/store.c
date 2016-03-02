#include "store.h"

#include <stdio.h>
#include <stdlib.h>

// Body array management functions
body** allocateBodyArray(int numBodies) {
  return 0;
}

int freeBodyArray(body* arrayBase) {
  return 0;
}

int freeFromArray(int index) {
  return 0;
}

// Calculation marking matrix
uint8_t** genMatrix(int squareSize) {
  // Create Pointer Variable
  uint8_t** matrixPtr;

  // Allocate Memory
  matrixPtr = malloc(sizeof(uint8_t *) * squareSize);
  for(int x = 0; x < squareSize; x++) {
    matrixPtr[x] = malloc(sizeof(uint8_t) * squareSize);
  }

  resetMatrix(matrixPtr, squareSize);

  return matrixPtr;
}

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

int freeMatrix(uint8_t** matrixBase, int cbc) {
  return 0;
}
