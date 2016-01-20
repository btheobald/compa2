#include <mutex>

class dataShare {
private:
  int testData;
  std::mutex testData_lock;

public:
  dataShare(int p_testData);
  ~dataShare();

  // Interfaces
  void setTestData(int p_testData);
  int getTestData();
}
