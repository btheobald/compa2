#include <iostream>
#include <vector>
#include "body.hpp"
#include "quadNode.hpp"

const int bodyCount = 10;

int main() {
  body b1(1, 1,  1, 0, 0, 1);
  body b2(1, 2, -4, 0, 0, 2);
  body b3(1, -4,  2, 0, 0, 3);
  body b4(1, -6,  2, 0, 0, 4);

  quadNode* root = new quadNode(0, 0, 10);
  std::cerr << "Body 1" << std::endl;
  root->insert(&b1);
  std::cerr << "Body 2" << std::endl;
  root->insert(&b2);
  std::cerr << "Body 3" << std::endl;
  root->insert(&b3);
  std::cerr << "Body 4" << std::endl;
  root->insert(&b4);

  /*std::vector<body> storage;

  for(int i = 0; i < bodyCount; i++) {
    storage.push_back(body());
  }

  std::cerr << "Done" << std::endl;
  while(1) {
    __asm__("nop");
  }*/

  std::cerr << "Printing Tree" << std::endl;
  root->recurseBID(0);
}
