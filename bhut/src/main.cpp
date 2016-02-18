#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "body.hpp"
#include "quadNode.hpp"
#include <GLFW/glfw3.h>

const int bodies = 1E7;

int main() {
  std::vector<body> storage;

  // Use Mersenne Twister for RNE within range.
  std::uniform_real_distribution<> pos(0, 100*2);
   // Use random device for seed value
  std::random_device r;
  std::mt19937 gen(r());

  double tempRand, tempCirX, tempCirY;

  for(int bIDC = 0; bIDC < bodies; bIDC++) {
    // Ensure that bodies are not too close to center.
    do tempRand = pos(gen) - 500; while((tempRand < 10) & (tempRand > -10));
    // Map to Circle
    tempCirX = tempRand * cos(2 * M_PI * tempRand);
    tempCirY = tempRand * sin(2 * M_PI * tempRand);
    storage.push_back(body(1, tempCirX, tempCirY, 0, 0));
  }

  //storage.push_back(body(1,  5,  0,  0, 0));
  //storage.push_back(body(1, -5,  0,  0,  0));

  quadNode* root = new quadNode(0, 0, 1000);
  for(int i = 0; i < bodies; i++) {
    root->insert(&storage[i]);
  }

  root->~quadNode();
}
