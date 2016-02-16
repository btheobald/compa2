#pragma once
#include "body.hpp"

class quadNode {
private:
  quadNode* ne, se, sw, nw;
  body pseudoBody;

public:
  quadNode();
  ~quadNode();
}
