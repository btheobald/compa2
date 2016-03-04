#ifndef STORE_DEF_GUARD
#define STORE_DEF_GUARD

#include <stdint.h>

#include "body.h"

// Body array management functions
body** allocateBodyArray(int cbc);  // Allocate memory for body array, return base pointer
int freeBodyArray(body** arrayBase, int cbc);  // Free memory used by body storage array

// Calculation marking matrix
uint8_t** genMatrix(int squareSize);      // Allocates memory for a 2D Matrix Array, parameter is side length, return base pointer (Type is 8 Bit unsigned int to reduce memory usage)
void resetMatrix(uint8_t** matrixPtr, int cbc); // Set to default state
int freeMatrix(uint8_t** matrixPtr, int cbc); // Free memory used by 2D Matrix Array.

#endif//STORE_DEF_GUARD
