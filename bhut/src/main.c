#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct body{
  int id;

  float m;
  
  float pX;
  float pY;
  
  float vX;
  float vY;
  
  float aX;
  float aY;
  
} body;

typedef struct bounds{
  float cX, cY;
  float half;
} bounds;

typedef struct node{
  struct node* northWest;
  struct node* northEast;
  struct node* southEast;
  struct node* southWest;
  
  bounds* boundary;
  
  body* nodeBody;
  
} node;

node* newNode(bounds* boundary) {
  // Allocate Memory to Heap
  node* n = malloc(sizeof(node));
  
  // Populate Boundary
  n->boundary = boundary;
  
  // Null Pointers
  n->northWest = NULL;
  n->northEast = NULL;
  n->southEast = NULL;
  n->southWest = NULL;

  n->nodeBody = NULL;
  
  // Return Allocated Pointer
  return n;
}

// Deletes whole tree from called node.
int deleteNode(node* d) {
  // Recursively Traverse Tree
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
  
  // Free Node Memory Allocation
  free(d->boundary);
  if(d->nodeBody != NULL) {
    //printf("Freeing Body %d: X:%f, Y:%f\n", d->nodeBody->id, d->nodeBody->pX, d->nodeBody->pY);
    free(d->nodeBody);
  }
  free(d);
  
  // Return 1 to Signal Node Deletion
  return 1;
}

bounds* setBoundary(float cX, float cY, float half) {
  // Allocate Memory to Heap
  bounds* b = malloc(sizeof(bounds));
  
  // Assign Variables
  b->cX = cX;
  b->cY = cY;
  b->half = half;
  
  return b;
}

int subdivide(node* currentNode) {
  float cX, cY, half;
  
  // Create Short Access Copy of Bounds
  cX = currentNode->boundary->cX;
  cY = currentNode->boundary->cY;
  half = currentNode->boundary->half;
  
  // Create Subdivision Boundaries
  bounds* northWestBounds = setBoundary(cX-(half/2), cY+(half/2), half/2);
  bounds* northEastBounds = setBoundary(cX+(half/2), cY+(half/2), half/2);
  bounds* southEastBounds = setBoundary(cX+(half/2), cY-(half/2), half/2);
  bounds* southWestBounds = setBoundary(cX-(half/2), cY-(half/2), half/2);
  
  // Allocate Memory for New Nodes
  currentNode->northWest = newNode(northWestBounds);
  currentNode->northEast = newNode(northEastBounds);
  currentNode->southEast = newNode(southEastBounds);
  currentNode->southWest = newNode(southWestBounds);
  
  // Return 1 to signify successful subdivision
  return 1;
}

int checkBounds(body* pBody, node* currentNode) {
  float xMax, xMin, yMax, yMin;
  
  // Get Min and Max for X and Y
  xMax = currentNode->boundary->cX + currentNode->boundary->half;
  xMin = currentNode->boundary->cX - currentNode->boundary->half;
  yMax = currentNode->boundary->cY + currentNode->boundary->half;
  yMin = currentNode->boundary->cY - currentNode->boundary->half;
  
  // Check if Body is outside bounds
  if((pBody->pX < xMin) | (pBody->pX > xMax)) return 0;
  if((pBody->pY < yMin) | (pBody->pY > yMax)) return 0;
  // Else body is inside
  return 1;
}

body* newBody(float m, float pX, float pY, float vX, float vY, float id) {
  // Allocate Memory to Heap
  body* bp = malloc(sizeof(body));
  
  // Assign Initial Variables
  bp->id = id;
  bp->m  = m;
  bp->pX = pX;
  bp->pY = pY;
  bp->vX = vX;
  bp->vY = vY;
  
  // Insert into Tree
  return bp;
}

int insert(node* currentNode, body* pBody, int level) {
  // Return false if body does not belong in this node.
  if(!checkBounds(pBody, currentNode)) return 0;
  
  // Insert Body into Node
  if(currentNode->nodeBody == NULL) {
    currentNode->nodeBody = pBody;
    return 1;
  }
  
  // Subdivide Node
  if(currentNode->northWest == NULL) {
    subdivide(currentNode);
    insert(currentNode, currentNode->nodeBody, level+1);
    // TODO: Add body averaging
    currentNode->nodeBody = newBody(1,  -1,  -1,  0,  0, -1);
  }

  // Put point into Subtree
  if(insert(currentNode->northWest, pBody, level+1)) return 1; 
  if(insert(currentNode->northEast, pBody, level+1)) return 1;
  if(insert(currentNode->southEast, pBody, level+1)) return 1;
  if(insert(currentNode->southWest, pBody, level+1)) return 1;
  
  // Return false if point cannot be inserted.  
  return 0;
}

const int bodies = 1E7;

int main() {
  // Create Root Boundary and Tree Root.
  bounds* rootBounds = setBoundary(0, 0, 10000);
  node* root = newNode(rootBounds);
  
  // Create New Bodies
  int x, y, id = 0;
  for(x = -sqrt(bodies)/2; x <= sqrt(bodies)/2; x++) {
    for(y = -sqrt(bodies)/2; y <= sqrt(bodies)/2; y++) {
      body* tempInsert = newBody(1,  x,  y,  0,  0, id);
      // Free memory if insertion fails. 
      if(!insert(root, tempInsert, 0)) free(tempInsert);
    }
  }
  
  // Cleanup Tree
  deleteNode(root);
  
  return 0;
}

