#pragma once
#include <mutex>
using namespace std;

class dataShare {
private:
  int testData;
  mutex testData_lock;

public:
  dataShare(int p_testData);
  ~dataShare();

  // Interfaces
  void setTestData(int p_testData);
  int getTestData();
};
