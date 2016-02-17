#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "body.hpp"
#include "quadNode.hpp"
#include <GLFW/glfw3.h>

const int bodies = 10000000;

int main() {

  glfwInit();
  double timer;

  // Use Mersenne Twister for RNE within range.
  std::uniform_real_distribution<> pos(0, 10000*2);
   // Use random device for seed value
  std::random_device r;
  std::mt19937 gen(r());

  double tempRand, tempCirX, tempCirY;

  std::vector<body> storage;
  for(int bIDC = 0; bIDC < bodies; bIDC++) {
    // Ensure that bodies are not too close to center.
    do tempRand = pos(gen) - 100; while((tempRand < 10) & (tempRand > -10));
    // Map to Circle
    tempCirX = tempRand * cos(2 * M_PI * tempRand);
    tempCirY = tempRand * sin(2 * M_PI * tempRand);
    storage.push_back(body(1, tempCirX, tempCirY, 0, 0));
  }

  timer = (double)glfwGetTime();

  std::cerr << "Quad-Tree Begin" << std::endl;
  quadNode* root = new quadNode(0, 0, 5000);
  for(int i = 0; i < bodies; i++) {
    root->insert(std::move(&storage[i]));
  }
  std::cerr << "Quad-Tree End" << std::endl;

  std::cerr << "Time: " << (double)glfwGetTime()-timer << std::endl;

  root->~quadNode();

  //std::cerr << "Printing Tree" << std::endl;
  //root->recurseBID(0);
}
