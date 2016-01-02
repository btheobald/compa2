#include <iostream>
#include <vector>
using namespace std;

class MyClass
{
public:
  MyClass();
  MyClass(int a, int b);
  MyClass(int a, int b, int c);
  MyClass(int a, int b, int c[2]);
  ~MyClass();

private:

};

MyClass::MyClass() {
  cout << "A" << endl;
}

MyClass::MyClass(int a, int b) {
  cout << "B" << endl;
}

MyClass::MyClass(int a, int b, int c) {
  cout << "C" << endl;
}

MyClass::MyClass(int a, int b, int c[2]) {
  cout << "D" << endl;
}

MyClass::~MyClass() {
  cout << "Object Destroyed" << endl;
}

int main() {
  MyClass a;
  MyClass b(5, 1);
  MyClass c(7, 2, 1);
  int intsarray[2] = { 2, 4 };
  MyClass d(7, 2, intsarray);

  return 0;
}