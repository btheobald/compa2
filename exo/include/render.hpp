#pragma once

#include "scenario.hpp"

class render: public scenario {
private:
  void drawBody(body* p_b);
  void applyCamera(void);

public:
  void createSuperstructure(int p_soBodies, double p_cMass, double p_oMass, double p_cRadius, double p_oRadius, double p_cPosX, double p_cPosY, double p_cVelX, double p_cVelY, double p_coSpacing, double p_sRadius);
  void drawScene(void);

};
