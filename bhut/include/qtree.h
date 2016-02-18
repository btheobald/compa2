#ifndef QTREE_INCLUDE_GUARD
#define QTREE_INCLUDE_GUARD

#include "body.h"

// Node bsoundary
typedef struct bounds{
  // Center XY
  float cX, cY;
  // Distance from center
  float half;
} bounds;

// Allocate memory for boundary
bounds* setBoundary(float cX, float cY, float half);

// Node
typedef struct node{
  // Subdivided bode pointers
  struct node* northWest;
  struct node* northEast;
  struct node* southEast;
  struct node* southWest;

  // Node boundary pointer
  bounds* boundary;

  // Node body pointer
  body* nodeBody;
} node;

// Allocate memory for new node
node* newNode(bounds* boundary);
// Deallocate memory for node
int deleteNode(node* d);

// Insert body pointer into tree
int insert(node* currentNode, body* pBody, int level);
// Create subdivisions for node
int subdivide(node* currentNode);
// Check if body fits ino boundary
int checkBounds(body* pBody, node* currentNode);

#endif /* QTREE_INCLUDE_GUARD */
