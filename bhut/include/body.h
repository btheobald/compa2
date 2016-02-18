#ifndef BODY_INCLUDE_GUARD
#define BODY_INCLUDE_GUARD

typedef struct body{
  // Mass
  float m;
  // Position XY
  float pX;
  float pY;
  // Velocity XY
  float vX;
  float vY;
  // Acceleration XY
  float aX;
  float aY;
} body;

// Allocate Memory for New Body
body* newBody(float m, float pX, float pY, float vX, float vY);

#endif /* BODY_INCLUDE_GUARD */
