#pragma once
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
	void updateSharedArea(sharedStage* l_sharedDataAccess);
	void updateLocalStore(sharedStage* l_sharedDataAccess);
    // Render-Specific Functions Here
    void drawBody(int bodyID);
    void drawScene(void);
};
