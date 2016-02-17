#pragma once
#include "body.hpp"

class quadNode {
private:
  // Nodes
  quadNode* ne;
  quadNode* se;
  quadNode* sw;
  quadNode* nw;

  body* pseudoBody;                   // Actual body or center of mass

  double centerX, centerY;            // Square Center, used for subdivision
  double half;                        // Half Dimension, used for subdivision

  void subdivide();                   // Split Node into 4
  int checkPlace(body* p_addBody);    // Check if Body is in quad.
  void updateCOM();

public:
  quadNode();
  quadNode(double centerX, double centerY, double half);
  ~quadNode();

  int insert(body* p_addBody);
  void recurse(int level);
  inline float getM() { if(pseudoBody != NULL) return pseudoBody->getM(); return -1;};
};
