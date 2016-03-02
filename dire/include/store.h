#ifndef STORE_DEF_GUARD
#define STORE_DEF_GUARD

#include <stdint.h>

#include "body.h"

// Body array management functions
body** allocateBodyArray(int numBodies);  // Allocate memory for body array, return base pointer
int freeBodyArray(body* arrayBase);       // Free memory used by body storage array
int freeFromArray(int index);             // Free the item at the passed array position (reallocates and resizes Array)

// Calculation marking matrix
uint8_t** genMatrix(int squareSize);      // Allocates memory for a 2D Matrix Array, parameter is side length, return base pointer (Type is 8 Bit unsigned int to reduce memory usage)
int freeMatrix(uint8_t** matrixBase);     // Free memory used by 2D Matrix Array.

#endif//STORE_DEF_GUARD
