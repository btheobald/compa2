#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "qtree.h"

const int bodies = 16;

int main() {
  // Create Root Boundary and Tree Root.
  bounds* rootBounds = setBoundary(0, 0, 10000);
  node* root = newNode(rootBounds);

  // Create New Bodies
  int x, y;
  for(x = -sqrt(bodies)/2; x <= sqrt(bodies)/2; x++) {
    for(y = -sqrt(bodies)/2; y <= sqrt(bodies)/2; y++) {
      body* tempInsert = newBody(1,  x,  y,  0,  0);
      // Free memory if insertion fails.
      printf("Insert Body\n");
      if(!insert(root, tempInsert, 0)) free(tempInsert);
    }
  }

  /*body* tempInsert0 = newBody(1,  0,  0,  0,  0);
  body* tempInsert1 = newBody(1,  0,  1,  0,  1);
  //body* tempInsert2 = newBody(1,  1,  1,  0,  0);
  // Free memory if insertion fails.
  if(!insert(root, tempInsert0, 0)) free(tempInsert0);
  if(!insert(root, tempInsert1, 0)) free(tempInsert1);*/

  // Cleanup Tree
  deleteNode(root);

  return 0;
}
