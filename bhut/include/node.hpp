#pragma once
#include "aabb.hpp";
#include "point.hpp";

class quadNode {
public:
  const int NODE_CAPACITY = 4;

  aabb bounds;

  points nodeBodies[NODE_CAPACITY];

  quadNode* nodeFrom;
  quadNode* nodesTo[4];

  quadNode(aabb p_bounds);
  ~quadNode();

  insertBody(point p_body);
  subdivide();
  queryRange(aabb p_range);
};
