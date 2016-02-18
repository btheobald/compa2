#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "qtree.h"

const int bodies = 1E7;

int main() {
  // Create Root Boundary and Tree Root.
  bounds* rootBounds = setBoundary(0, 0, 5000);
  node* root = newNode(rootBounds);

  /*// Create New Bodies
  int x, y;
  for(x = -sqrt(bodies)/2; x <= sqrt(bodies)/2; x++) {
    for(y = -sqrt(bodies)/2; y <= sqrt(bodies)/2; y++) {
      body* tempInsert = newBody(1,  x,  y,  0,  0);
      // Free memory if insertion fails.
      if(!insert(root, tempInsert, 0)) free(tempInsert);
    }
  }*/

  body* tempInsert = newBody(1,  0,  0,  0,  0);
  // Free memory if insertion fails.
  if(!insert(root, tempInsert, 0)) free(tempInsert);

  // Cleanup Tree
  deleteNode(root);

  return 0;
}
