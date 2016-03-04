#ifndef STORE_DEF_GUARD
#define STORE_DEF_GUARD

#include <stdint.h>

#include "body.h"

// Body array management functions
// Allocate memory for body array, return base pointer
body** allocateBodyArray(int cbc);
// Free memory used by body storage array
int freeBodyArray(body** arrayBase, int cbc);

// Calculation marking matrix
// Allocates memory for a 2D Matrix Array, parameter is side length, return base pointer (Type is 8 Bit unsigned int to reduce memory usage)
uint8_t** genMatrix(int squareSize);
// Set to default state
void resetMatrix(uint8_t** matrixPtr, int cbc);
// Free memory used by 2D Matrix Array.
int freeMatrix(uint8_t** matrixPtr, int cbc);

#endif//STORE_DEF_GUARD
