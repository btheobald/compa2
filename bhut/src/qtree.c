#include <stdio.h>
#include <stdlib.h>

#include "qtree.h"

int insert(node* currentNode, body* pBody, int level) {
  // Return false if body does not belong in this node.
  if(!checkBounds(pBody, currentNode)) return 0;

  // Insert body into node
  if(currentNode->nodeBody == NULL) {
    currentNode->nodeBody = pBody;
    return 1;
  }

  // Prevent adding body to same location
  if((currentNode->nodeBody->pX == pBody->pX) & (currentNode->nodeBody->pY == pBody->pY)) {
    return 0;
  }

  // Subdivide node
  if(currentNode->northWest == NULL) {
    subdivide(currentNode);
    insert(currentNode, currentNode->nodeBody, level+1);
    // TODO: Add body averaging
    currentNode->nodeBody = newBody(1,  -1,  -1,  0,  0);
  }

  // Put point into subtree
  if(insert(currentNode->northWest, pBody, level+1)) return 1;
  if(insert(currentNode->northEast, pBody, level+1)) return 1;
  if(insert(currentNode->southEast, pBody, level+1)) return 1;
  if(insert(currentNode->southWest, pBody, level+1)) return 1;

  // Return false if point cannot be inserted.
  return 0;
}

node* newNode(bounds* boundary) {
  // Allocate memory to heap
  node* n = malloc(sizeof(node));

  // Populate boundary
  n->boundary = boundary;

  // Null pointers
  n->northWest = NULL;
  n->northEast = NULL;
  n->southEast = NULL;
  n->southWest = NULL;
  n->nodeBody = NULL;

  // Return allocated pointer
  return n;
}

// Deletes whole tree from called node.
int deleteNode(node* d) {
  // Recursively traverse tree
  if(d->northWest != NULL) {
    deleteNode(d->northWest);
    d->northWest = NULL;
  }
  if(d->northEast != NULL) {
    deleteNode(d->northEast);
    d->northEast = NULL;
  }
  if(d->southEast != NULL) {
    deleteNode(d->southEast);
    d->southEast = NULL;
  }
  if(d->southWest != NULL) {
    deleteNode(d->southWest);
    d->southWest = NULL;
  }

  // Free boundary memory allocation
  free(d->boundary);
  // Free body memory allocation
  deleteBody(d->nodeBody);
  // Free node memory allocation
  free(d);

  // Return 1 to signal node deletion
  return 1;
}

bounds* setBoundary(float cX, float cY, float half) {
  // Allocate memory to heap
  bounds* b = malloc(sizeof(bounds));

  // Assign variables
  b->cX = cX;
  b->cY = cY;
  b->half = half;

  return b;
}

int subdivide(node* currentNode) {
  float cX, cY, half;

  // Create short access copy of bounds
  cX = currentNode->boundary->cX;
  cY = currentNode->boundary->cY;
  half = currentNode->boundary->half;

  // Create subdivision boundaries
  bounds* northWestBounds = setBoundary(cX-(half/2), cY+(half/2), half/2);
  bounds* northEastBounds = setBoundary(cX+(half/2), cY+(half/2), half/2);
  bounds* southEastBounds = setBoundary(cX+(half/2), cY-(half/2), half/2);
  bounds* southWestBounds = setBoundary(cX-(half/2), cY-(half/2), half/2);

  // Allocate memory for new nodes
  currentNode->northWest = newNode(northWestBounds);
  currentNode->northEast = newNode(northEastBounds);
  currentNode->southEast = newNode(southEastBounds);
  currentNode->southWest = newNode(southWestBounds);

  // Return 1 to signify successful subdivision
  return 1;
}

int checkBounds(body* pBody, node* currentNode) {
  float xMax, xMin, yMax, yMin;

  // Get min and max for X and Y
  xMax = currentNode->boundary->cX + currentNode->boundary->half;
  xMin = currentNode->boundary->cX - currentNode->boundary->half;
  yMax = currentNode->boundary->cY + currentNode->boundary->half;
  yMin = currentNode->boundary->cY - currentNode->boundary->half;

  // Check if body is outside bounds
  if((pBody->pX < xMin) | (pBody->pX > xMax)) return 0;
  if((pBody->pY < yMin) | (pBody->pY > yMax)) return 0;
  // Else body is inside
  return 1;
}
