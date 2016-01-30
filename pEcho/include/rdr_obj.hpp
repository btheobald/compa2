#pragma once
#include "scenario.hpp"
#include "body.hpp"
#include <cmath>
#include <GLFW/glfw3.h>

class rdr_obj : public scenario {
  // Render-Specific Functions Here
  public:
    void drawBody(int bodyID);
};
