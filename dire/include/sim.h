#ifndef SIM_DEF_GUARD
#define SIM_DEF_GUARD

#include <stdint.h>

#include "body.h"

// Distance
// Find the x/y distance bettween two bodies
float getComponentDistance(body* bA, body* bB, int xy);
// Find vector/total distance bettwen two bodies
float getVectorDistance(body* bA, body* bB);

// Calculate Forces
// Return true/false if force calculation is needed
int checkIfNeeded(uint8_t** forceMark, int bA, int bB);
// Calculate acceleration bettween two bodies, using force calculation and mass, returns value
void calculateAcceleration(float gc, body* bA, body* bB);

// Itteration call, pass current body count
void itteration(body** bodyArray, int cbc, float gc, float dt);

#endif//SIM_DEF_GUARD
