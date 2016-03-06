#pragma once

#include "scenario.hpp"

class render: public scenario {
private:
  void drawBody(body* p_b);
  void applyCamera(void);

public:
  void createSuperstructure();
  void drawScene(void);

};
