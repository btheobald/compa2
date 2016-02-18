#pragma once
#include <GLFW/glfw3.h>   // GLFW
#include <iostream>
#include <AntTweakBar.h>  // AntTweakBar

// This class acts as a tider interface for ATB and GLFW?
class interface {
  private:
    // Windows
    TwBar* simInterface;
    TwBar* bodyInterface;
    TwBar* systemInterface;
    TwBar* dialog;

    // Sim Control
    double UGC_I = 0;
    double IDT_I = 0;
    int IPF_I = 0;

    // Pause / Run
    bool paused_I = false;
    // Current bodies in simulation
    int numBodies = 0;
    // Flag if Collisions should be calculated
    bool doCollisions = true;

    // Active Body Interface
    int abID_I = 0;
    double abMass_I = 0;
    double abRadius_I = 0;
    double abPositionX_I = 0;
    double abPositionY_I = 0;
    double abVelocityX_I = 0;
    double abVelocityY_I = 0;
    double abForceX_I = 0;
    double abForceY_I = 0;
    double abAccelerationX_I = 0;
    double abAccelerationY_I = 0;
    bool abFixed_I = false;
    float abColor_I[3] = {0.0f, 0.0f, 0.0f};

    std::string fileName = "Default.sav";

    // Sim and System Interface Setup, Will be called once at start.
    void setupSimInterface();
    void setupSystemInterface();

    // Dialog setup, tbd.
    void setupDialog();

  public:
    interface(int p_wXRes, int p_wYRes);
    ~interface();

    // Body Interface Setup, Will be called throughout program, handled by Main.
    void setupBodyInterface(int p_abID);
    void updateScenario(rdr_obj* localScenario);
    void updateInterface(rdr_obj* localScenario);
    void updateActiveID(int p_bodyID);
};

// Class External Callbacks
void TW_CALL saveFileButton(void *);
void TW_CALL loadFileButton(void *);

// Filename should always have a string and must have a .sav file extension.
void TW_CALL handleFilename(std::string& destinationClientString, const std::string& sourceLibraryString);

void TW_CALL deleteBodyButton(void *);
