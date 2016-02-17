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
    double UGC_I;
    double IDT_I;
    int IPF_I = 0;

    // Pause / Run
    bool paused_I;
    // Current bodies in simulation
    int numBodies;
    // Flag if Collisions should be calculated
    bool doCollisions;

    // Active Body Interface
    int abID_I;
    double abMass_I;
    double abRadius_I;
    double abPositionX_I;
    double abPositionY_I;
    double abVelocityX_I;
    double abVelocityY_I;
    double abForceX_I;
    double abForceY_I;
    double abAccelerationX_I;
    double abAccelerationY_I;
    bool abFixed_I;

    std::string fileName;

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
};

// Class External Callbacks
void saveFile(void *);
void loadFile(void *);
