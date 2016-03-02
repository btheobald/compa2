#ifndef SIM_DEF_GUARD
#define SIM_DEF_GUARD

#include <stdint.h>

#include "body.h"

// Distance
float getComponentDistance(body* bA, body* bB, int xy);   // Find the x/y distance bettween two bodies
float getVectorDistance(body* bA, body* bB);              // Find vector/total distance bettwen two bodies

// Calculate Forces
int checkIfNeeded(uint8_t** forceMark, int bA, int bB);    // Return true/false if force calculation is needed
int markCalculation(uint8_t** forceMark, int bA, int bB, uint8_t status);  // Mark force matrix position with status passed
void calculateAcceleration(float gc, body* bA, body* bB);          // Calculate acceleration bettween two bodies, using force calculation and mass, returns value

void itteration(body** bodyArray, int cbc, float gc, float dt); // Itteration call, pass current body count

#endif//SIM_DEF_GUARD
