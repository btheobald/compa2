#pragma once
#include <GLFW/glfw3.h>   // GLFW
#include <iostream>
#include <AntTweakBar.h>  // AntTweakBar

// This class acts as a tider interface for ATB and GLFW?
class interface {
  private:
    TwBar* simInterface;
    TwBar* bodyInterface;
    TwBar* systemInterface;
    TwBar* dialog;

    // Sim Control
    double UGC_I;
    double IDT_I;
    double IPF_I;


    // Active Body Interface
    int abID_I;
    double abMass_I;
    double abPosX_I;
    double abPosY_I;
    double abVelX_I;
    double abVelY_I;
    bool abFixed_I;

    // Sim and System Interface Setup, Will be called once at start.
    void setupSimInterface();
    void setupSystemInterface();

    // Dialog setup, tbd.
    void setupDialog();

  public:
    bool paused_I;
    interface(int p_wXRes, int p_wYRes);
    ~interface();

    // Body Interface Setup, Will be called throughout program, handled by Main.
    void setupBodyInterface(int p_abID);
};
