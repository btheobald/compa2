#pragma once
#include "point.hpp"

class aabb {
public:
  point center;
  float half;

  aabb(point p_center, float p_half);
  ~aabb();

  containsBody(point p_body);
  intersectAABB(aabb p_other);
};
