#include <iostream>
#include <vector>
#include <cmath>
#include "body.hpp"
#include "quadNode.hpp"

const int bodies = 1E5;

int main() {
  std::vector<body> storage;
  for(int x = 0; x < sqrt(bodies); x++) {
    for(int y = 0; y < sqrt(bodies); y++) {
      storage.push_back(body(1, x*100, y*100-bodies/2, 0, 0, (x+y)));
    }
  }

  quadNode* root = new quadNode(0, 0, 1000000000);
  for(int i = 0; i < bodies; i++) {
    root->insert(&storage[i]);
  }

  std::cerr << "Done" << std::endl;

  //std::cerr << "Printing Tree" << std::endl;
  //root->recurseBID(0);
}
