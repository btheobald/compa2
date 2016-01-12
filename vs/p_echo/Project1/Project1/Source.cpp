#include <iostream>

int main() {
  int al0[] = {1, 2};
  int al1[] = {*al0, 3};
  int al2[] = {*al1, 4};
  int al3[] = {*al2, 5};
  int al4[] = {*al3, 6};

  std::cout << al4[0] << std::endl;

  while (1) {}
  return 0;
}