#include <iostream>
#include <vector>
#include "body.hpp"

const int bodyCount = 10;

int main() {
  std::vector<body> storage;

  for(int i = 0; i < bodyCount; i++) {
    storage.push_back(body());
  }

  std::cerr << "Done" << std::endl;
  while(1) {
    __asm__("nop");
  }
}
