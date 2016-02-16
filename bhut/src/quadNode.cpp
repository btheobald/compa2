#include "quadNode.hpp"
#include <iostream>

quadNode::quadNode() {

}

quadNode::quadNode(double p_centerX, double p_centerY, double p_half) {
  centerX = p_centerX;
  centerY = p_centerY;
  half = p_half;

  pseudoBody = NULL;
  ne = NULL;
  se = NULL;
  sw = NULL;
  nw = NULL;
}

quadNode::~quadNode() {
  if(ne != NULL) {
    ne->~quadNode();
  }
  if(se != NULL) {
    se->~quadNode();
  }
  if(sw != NULL) {
    sw->~quadNode();
  }
  if(nw != NULL) {
    nw->~quadNode();
  }
}

void quadNode::subdivide() {
  //std::cerr << "Subdivision : " << r_depth << std::endl;

  //std::cerr << "NE Quad : " << centerX+(half/2) << " " << centerY+(half/2) << " " << half/2 << std::endl;
  //std::cerr << "SE Quad : " << centerX+(half/2) << " " << centerY-(half/2) << " " << half/2 << std::endl;
  //std::cerr << "SW Quad : " << centerX-(half/2) << " " << centerY-(half/2) << " " << half/2 << std::endl;
  //std::cerr << "NW Quad : " << centerX-(half/2) << " " << centerY+(half/2) << " " << half/2 << std::endl;

  ne = new quadNode(centerX+(half/2), centerY+(half/2), half/2);
  se = new quadNode(centerX+(half/2), centerY-(half/2), half/2);
  sw = new quadNode(centerX-(half/2), centerY-(half/2), half/2);
  nw = new quadNode(centerX-(half/2), centerY+(half/2), half/2);
}

int quadNode::checkPlace(body* p_addBody) {
  //std::cerr << "Check : " << r_depth << std::endl;
  // Check X
  if((p_addBody->getP(0) > centerX-half) & (p_addBody->getP(0) <= centerX+half)) {
    if((p_addBody->getP(1) > centerY-half) & (p_addBody->getP(1) <= centerY+half)) {
      return true;
    }
  }
  // Return False if Body does Not Belong in Quad
  return false;
}

void quadNode::updateCOM() {

}

int quadNode::insert(body* p_addBody) {
  if(checkPlace(p_addBody)) {
    if(pseudoBody == NULL) {
      pseudoBody = p_addBody;
      return true;
    } else {
      if(ne == NULL) { // If ne is NULL, subdivide has not been called yet.
        subdivide();
        // Put Old Body Into Subdivided Tree
        insert(pseudoBody);
        updateCOM();
      }
      // Put new body into subdivied tree
      // Handle New Body
      if(ne->insert(p_addBody)) {
        *pseudoBody = (*pseudoBody+*p_addBody);
        return true;
      }
      if(se->insert(p_addBody))  {
        *pseudoBody = (*pseudoBody+*p_addBody);
        return true;
      }
      if(sw->insert(p_addBody)) {
        *pseudoBody = (*pseudoBody+*p_addBody);
        return true;
      }
      if(nw->insert(p_addBody))  {
        *pseudoBody = (*pseudoBody+*p_addBody);
        return true;
      }
    }
  }
  // Return False if Invalid Quad
  return false;
}

void quadNode::recurse(int level) {
  if(ne != NULL) {
    //std::cerr << " vNEv" << std::endl;
    ne->recurse(level+1);
  }
  if(se != NULL) {
    //std::cerr << " vSEv" << std::endl;
    se->recurse(level+1);
  }
  if(sw != NULL) {
    //std::cerr << " vSWv" << std::endl;
    sw->recurse(level+1);
  }
  if(nw != NULL) {
    //std::cerr << " vNWv" << std::endl;
    nw->recurse(level+1);
  }
  //std::cerr << " ^" << std::endl;
}
