#ifndef BODY_DEF_GUARD
#define BODY_DEF_GUARD

typedef struct {
  // Acceleration // Second Derrirative - Rate of change
  float aX;
  float aY;
  // Velocity // First Derrirative - Change
  float vX;
  float vY;
  // Position // Base Quantity - Distance
  float pX;
  float pY;

  // Mass
  float m; // Base Quantity - Reluctance to move
} body;

// Position, Velocity and Acceleration Calculations
void calculatePosition(body* bd, float dt);
void calculateVelocity(body* bd, float dt);

#endif//BODY_DEF_GUARD
