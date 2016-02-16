#pragma once
#include "body.hpp"

class quadNode {
private:
  // Nodes
  quadNode* ne;
  quadNode* se;
  quadNode* sw;
  quadNode* nw;

  body* pseudoBody;          // Actual body or center of mass

  double centerX, centerY;  // Square Center, used for subdivision
  double half;              // Half Dimension, used for subdivision

  void subdivide(int r_depth);         // Split Node into 4
  int checkPlace(body* p_addBody, int r_depth);  // Check if Body is in quad.

public:
  quadNode();
  quadNode(double centerX, double centerY, double half);
  ~quadNode();

  int insert(body* p_addBody, int r_depth);
};
