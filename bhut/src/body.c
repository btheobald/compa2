#include <stdio.h>
#include <stdlib.h>

#include "body.h"

body* newBody(float m, float pX, float pY, float vX, float vY) {
  // Allocate Memory to Heap
  body* bp = malloc(sizeof(body));

  // Assign Initial Variables
  //bp->id = id;
  bp->m  = m;
  bp->pX = pX;
  bp->pY = pY;
  bp->vX = vX;
  bp->vY = vY;

  // Insert into Tree
  return bp;
}

int deleteBody(body* db) {
  if(db != NULL) {
    // Free body Memory Assignment
    free(db);
    return 1;
  }
  return 0;
}
