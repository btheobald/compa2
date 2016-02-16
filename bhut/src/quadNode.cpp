#include "quadNode.hpp"
#include <iostream>

quadNode::quadNode() {

}

quadNode::quadNode(double p_centerX, double p_centerY, double p_half) {
  centerX = p_centerX;
  centerY = p_centerY;
  half = p_half;
  pseudoBody = NULL;

  neMark = false;
  seMark = false;
  swMark = false;
  nwMark = false;

  hasChildren = false;
}

quadNode::~quadNode() {

}

void quadNode::subdivide() {
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

int quadNode::checkPlace(body* p_addBody) {
  //std::cerr << "Check : " << r_depth << std::endl;
  // Check X
  if((p_addBody->getP(0) >= centerX-half) & (p_addBody->getP(0) < centerX+half)) {
    if((p_addBody->getP(1) >= centerY-half) & (p_addBody->getP(1) < centerY+half)) {
      return true;
    }
  }
  // Return False if Body does Not Belong in Quad
  return false;
}

int quadNode::insertSubDiv(body* p_addBody) {
  //neMark = false;
  //seMark = false;
  //swMark = false;
  //neMark = false;

  // Handle New Body
  if(ne->insert(p_addBody)) {
    //std::cerr << "NE Good" << std::endl;
    neMark = true;
    return true;
  }
  if(se->insert(p_addBody))  {
    //std::cerr << "SE Good" << std::endl;
    seMark = true;
    return true;
  }
  if(sw->insert(p_addBody)) {
    //std::cerr << "SW Good" << std::endl;
    swMark = true;
    return true;
  }
  if(nw->insert(p_addBody))  {
    //std::cerr << "NW Good" << std::endl;
    nwMark = true;
    return true;
  }
  return false;
}

int quadNode::insert(body* p_addBody) {
  //std::cerr << "Insert : " << r_depth << std::endl;
  if(checkPlace(p_addBody)) {
    if(pseudoBody == NULL) {
      pseudoBody = p_addBody;
      return true;
    } else {
      if(!hasChildren) { // If nw is NULL, subdivide has not been called yet.
        subdivide();
        hasChildren = true;
        // Put Old Body Into Subdivided Tree
        insertSubDiv(pseudoBody);
      } else {
        //std::cerr << "Already Subdivided" << std::endl;
      }
      // Put new body into subdivied tree
      return insertSubDiv(p_addBody);
    }
  }

  // Return False if Invalid Quad
  return false;
}

void quadNode::recurseBID(int level) {
  std::cerr << level << ": " << " " << pseudoBody->getID() << std::endl;

  if(hasChildren) {
    if(neMark) {
      std::cerr << "NE ";
      ne->recurseBID(level++);
    }
    if(seMark) {
      std::cerr << "SE ";
      se->recurseBID(level++);
    }
    if(swMark) {
      std::cerr << "SW ";
      sw->recurseBID(level++);
    }
    if(nwMark) {
      std::cerr << "NW ";
      nw->recurseBID(level++);
    }
  }
}
