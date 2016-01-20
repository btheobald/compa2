#include <iostream>
#include <thread>
#include "dataShare.h"

using namespace std;

void workerCall(dataShare* sharePtr) {
  for(int i=0; i<100; i++) {
    sharePtr -> setTestData(i);
  }
}

int main() {
  // Create dataShare object
  dataShare testShare(5);

  cout << testShare.getTestData() << endl;

  // Create Thread, pass pointer to object
  thread worker(workerCall, &testShare);

  while(testShare.getTestData() != 99) {
    cout << testShare.getTestData() << endl;
  }

  worker.join();

  return 0;
}
