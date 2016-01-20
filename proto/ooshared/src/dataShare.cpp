#include "dataShare.h"

dataShare::dataShare(int p_testData) {
  testData = p_testData;
}

dataShare::~dataShare() {

}

void dataShare::setTestData(int p_testData) {
  testData_lock.lock();
  testData = p_testData;
  testData_lock.unlock();
}

int dataShare::getTestData() {
  testData_lock.lock();
  int testDataCpy = testData;
  testData_lock.unlock();

  return testDataCpy;
}
