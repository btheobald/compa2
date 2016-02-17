#include "interface.hpp"

interface::interface(int p_wXRes, int p_wYRes) {
  // Init AntTweakBar
  TwInit(TW_OPENGL, NULL);
  TwWindowSize(p_wXRes, p_wYRes);

  simInterface = TwNewBar("Simulation");
  bodyInterface = TwNewBar("Body");
  systemInterface = TwNewBar("System");

  setupSimInterface();
  setupBodyInterface(1);
  setupSystemInterface();

  // Set Globals
  TwDefine(" GLOBAL contained=true ");
}

interface::~interface() {

}

void interface::setupSimInterface() {
  // Color
  TwDefine(" 'Simulation' color='255 255 255' alpha=150 text=dark");

  // Size
  TwDefine(" 'Simulation' size='250 150'");
  TwDefine(" 'Simulation' resizable=false ");

  // Variables
  TwAddVarRW(simInterface, "UGCVar", TW_TYPE_DOUBLE, &UGC_I, " min=1E-12  max=10   step=0.01  label='Gravitational Constant' ");
  TwAddVarRW(simInterface, "IDTVar", TW_TYPE_DOUBLE, &IDT_I, " min=1E-6   max=1E9  step=0.01  label='Itteration Delta Time' ");
  TwAddVarRW(simInterface, "IPFVar", TW_TYPE_DOUBLE, &IPF_I, " min=0      max=1E4  step=0.01  label='Itterations Per Frame' ");
  TwAddVarRW(simInterface, "Paused", TW_TYPE_BOOLCPP, &paused_I, "label='Paused' ");
  //TwAddButton(simInterface, "PauseBtn", toggleBool, NULL, " label='Pause' ");
}
void interface::setupBodyInterface(int p_abID) {
  // Color
  TwDefine(" 'Body' color='255 255 255' alpha=150 text=dark");

  // Size
  TwDefine(" 'Body' size='250 300'");
  TwDefine(" 'Body' resizable=false ");
}
void interface::setupSystemInterface() {
  // Color
  TwDefine(" 'System' color='255 255 255' alpha=150 text=dark");

  // Size
  TwDefine(" 'System' size='250 300'");
  TwDefine(" 'System' resizable=false ");
}
void interface::setupDialog() {

}
