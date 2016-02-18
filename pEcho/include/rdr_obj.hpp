#pragma once
// Standard Library Includes
#include <random>
#include <iostream>
// External Library Includes
#include <GLFW/glfw3.h> // GLFW
// Custom Includes
#include "scenario.hpp"
#include "body.hpp"
#include "sharedStage.hpp"
#include "com.hpp"

class rdr_obj : public scenario {
public:
	// Management Functions
	void setupDefaultScenario();
  void createSuperstructure(int p_soBodies, double p_cMass, double p_oMass, double p_cRadius, double p_oRadius, double p_cPosX, double p_cPosY, double p_cVelX, double p_cVelY, double p_coSpacing, double p_sRadius, const float p_Color[3]);
  void updateSharedArea(sharedStage* l_sharedDataAccess);
  void updateLocalStore(sharedStage* l_sharedDataAccess);
  // Render-Specific Functions Here
  void drawBody(int bodyID);
  void drawScene(void);
  // Check Coordinates
  int checkCoord(double x, double y);

  // WARNING : BREAKS ENCAPSULATION
  body* getBodyPointer(int bodyID);
};
