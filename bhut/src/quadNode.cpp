#include "quadNode.hpp"
#include <iostream>

quadNode::quadNode() {

}

quadNode::quadNode(double p_centerX, double p_centerY, double p_half) {
  centerX = p_centerX;
  centerY = p_centerY;
  half = p_half;
  pseudoBody = NULL;
}

quadNode::~quadNode() {

}

void quadNode::subdivide(int r_depth) {
  //std::cerr << "Subdivision : " << r_depth << std::endl;

  std::cerr << "NE Quad : " << centerX+(half/2) << " " << centerY+(half/2) << " " << half/2 << std::endl;
  std::cerr << "SE Quad : " << centerX+(half/2) << " " << centerY-(half/2) << " " << half/2 << std::endl;
  std::cerr << "SW Quad : " << centerX-(half/2) << " " << centerY-(half/2) << " " << half/2 << std::endl;
  std::cerr << "NW Quad : " << centerX-(half/2) << " " << centerY+(half/2) << " " << half/2 << std::endl;

  ne = new quadNode(centerX+(half/2), centerY+(half/2), half/2);
  se = new quadNode(centerX+(half/2), centerY-(half/2), half/2);
  sw = new quadNode(centerX-(half/2), centerY-(half/2), half/2);
  nw = new quadNode(centerX-(half/2), centerY+(half/2), half/2);
}

int quadNode::checkPlace(body* p_addBody, int r_depth) {
  //std::cerr << "Check : " << r_depth << std::endl;
  // Check X
  if((p_addBody->getP(0) > centerX-half) & (p_addBody->getP(0) < centerX+half)) {
    if((p_addBody->getP(1) > centerY-half) & (p_addBody->getP(1) < centerY+half)) {
      return true;
    }
  }
  // Return False if Body does Not Belong in Quad
  return false;
}

int quadNode::insert(body* p_addBody, int r_depth) {
  //std::cerr << "Insert : " << r_depth << std::endl;
  r_depth++;
  if(checkPlace(p_addBody, r_depth)) {
    if(pseudoBody == NULL) {
      pseudoBody = p_addBody;
      return true;
    } else {
      if(nw == NULL) { // If nw is NULL, subdivide has not been called yet.
        subdivide(r_depth);
      } else {
        std::cerr << "Already Subdivided" << std::endl;
      }

      // Handle New Body
      if(ne->insert(p_addBody, r_depth)) {
        std::cerr << "NE Good" << std::endl;
        return true;
      }
      if(se->insert(p_addBody, r_depth))  {
        std::cerr << "SE Good" << std::endl;
        return true;
      }
      if(sw->insert(p_addBody, r_depth)) {
        std::cerr << "SW Good" << std::endl;
        return true;
      }
      if(nw->insert(p_addBody, r_depth))  {
        std::cerr << "NW Good" << std::endl;
        return true;
      }
    }
  }
  // Return False if Invalid Quad
  return false;
}
