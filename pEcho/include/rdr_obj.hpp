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
  void createSuperstructure(int p_soBodies, float p_cMass, float p_oMass, float p_cRadius, float p_oRadius, float p_cPosX, float p_cPosY, float p_cVelX, float p_cVelY, float p_coSpacing, float p_sRadius, const float p_Color[3]);
  void updateSharedArea(sharedStage* l_sharedDataAccess);
  void updateLocalStore(sharedStage* l_sharedDataAccess);
  // Render-Specific Functions Here
  void drawBody(int bodyID);
  void drawScene(void);
  // Check Coordinates
  int checkCoord(float x, float y);
};
