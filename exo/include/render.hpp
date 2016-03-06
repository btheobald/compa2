#include "scenario.hpp"

class render: public scenario {
private:
  void drawBody();
  void applyCamera();

public:
  void createSuperstructure();
  void drawScene();

};
