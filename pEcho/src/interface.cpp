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
  TwDefine(" GLOBAL fontresizable=false ");
  TwDefine(" GLOBAL fontstyle=default ");
  TwDefine(" GLOBAL buttonalign=center");
}

interface::~interface() {

}

void interface::setupSimInterface() {
  // Color
  TwDefine(" 'Simulation' color='255 255 255' alpha=150 text=dark");

  // Size
  TwDefine(" 'Simulation' size='300 180'");
  TwDefine(" 'Simulation' position='0 0'");
  TwDefine(" 'Simulation' resizable=false ");
  TwDefine(" 'Simulation' valueswidth=100 ");
  TwDefine(" 'Simulation' movable=false");

  // Control
  TwAddVarRW(simInterface, "ugcvar", TW_TYPE_DOUBLE,  &UGC_I,        " min=1E-12  max=10   step=0.01  precision=7   label='Gravitational Constant'  group=Control ");
  TwAddVarRW(simInterface, "idtvar", TW_TYPE_DOUBLE,  &IDT_I,        " max=-1E9   max=1E9  step=0.01  precision=7   label='Itteration Delta Time'   group=Control ");
  TwAddVarRW(simInterface, "collid", TW_TYPE_BOOLCPP, &doCollisions, " true=On      false=Off                       label='Simulate Collisions'     group=Control ");
  // Runtime
  TwAddVarRW(simInterface, "paused", TW_TYPE_BOOLCPP, &paused_I,     " true=Paused  false=Running                   label='Run/Pause'               group=Runtime ");
  TwAddVarRW(simInterface, "ipfvar", TW_TYPE_INT32,   &IPF_I,        " min=1      max=10000  step=1                   label='Itterations Per Frame'   group=Runtime ");
  // Statistics
  TwAddVarRO(simInterface, "numbod", TW_TYPE_INT32,   &numBodies,    "                                              label='Number of Bodies'        group=Statistics ");
}
void interface::setupBodyInterface(int p_abID) {
  // Color
  TwDefine(" 'Body' color='255 255 255' alpha=150 text=dark");

  // Size
  TwDefine(" 'Body' size='300 310'");
  TwDefine(" 'Body' position='0 182'");
  TwDefine(" 'Body' resizable=false ");
  TwDefine(" 'Body' valueswidth=100 ");
  TwDefine(" 'Body' movable=false");

  TwAddVarRO(bodyInterface, "bodyid", TW_TYPE_INT32, &abID_I,        "                                              label='Selected Body ID' ");
  TwAddVarRW(bodyInterface, "bdmass", TW_TYPE_DOUBLE,  &abMass_I,    " min=1E-3  max=1E40 step=1      precision=7   label='Mass'                    group=Properties ");
  TwAddVarRW(bodyInterface, "bdradi", TW_TYPE_DOUBLE,  &abRadius_I,  " min=1E-3  max=1E20 step=1      precision=7   label='Radius'                  group=Properties ");
  TwAddVarRW(bodyInterface, "bdfixd", TW_TYPE_BOOLCPP, &abFixed_I,   " true=Yes      false=No                       label='Fixed'                   group=Properties ");
  TwAddVarRW(bodyInterface, "bdcolr", TW_TYPE_COLOR3F, &abColor_I,   " coloralpha=false                             label='Colour'                  group=Properties ");

  TwAddVarRW(bodyInterface, "bdposx", TW_TYPE_DOUBLE, &abPositionX_I,     " min=-1E15 max=1E40 step=1 precision=7   label='X'                       group=Position ");
  TwAddVarRW(bodyInterface, "bdposy", TW_TYPE_DOUBLE, &abPositionY_I,     " min=-1E15 max=1E15 step=1 precision=7   label='Y'                       group=Position ");
  TwAddVarRW(bodyInterface, "bdvelx", TW_TYPE_DOUBLE, &abVelocityX_I,     " min=-3E8  max=3E8  step=1 precision=7   label='X'                       group=Velocity ");
  TwAddVarRW(bodyInterface, "bdvely", TW_TYPE_DOUBLE, &abVelocityY_I,     " min=-3E8  max=3E8  step=1 precision=7   label='Y'                       group=Velocity ");
  TwAddVarRO(bodyInterface, "bdaccx", TW_TYPE_DOUBLE, &abAccelerationX_I, "                           precision=7   label='X'                       group=Acceleration ");
  TwAddVarRO(bodyInterface, "bdaccy", TW_TYPE_DOUBLE, &abAccelerationY_I, "                           precision=7   label='Y'                       group=Acceleration ");
  TwAddVarRO(bodyInterface, "bdforx", TW_TYPE_DOUBLE, &abForceX_I,        "                           precision=7   label='X'                       group=Force ");
  TwAddVarRO(bodyInterface, "bdfory", TW_TYPE_DOUBLE, &abForceY_I,        "                           precision=7   label='Y'                       group=Force ");

  TwAddButton(bodyInterface,"delbody", deleteBodyButton, NULL, " label='Delete Body' ");
}
void interface::setupSystemInterface() {
  // Color
  TwDefine(" 'System' color='255 255 255' alpha=150 text=dark");

  // Size
  TwDefine(" 'System' size='300 90'");
  TwDefine(" 'System' position='0 494'");
  TwDefine(" 'System' resizable=false ");
  TwDefine(" 'System' valueswidth=100 ");
  TwDefine(" 'System' movable=false");

  TwCopyStdStringToClientFunc(handleFilename);
  TwAddVarRW(systemInterface, "filenm", TW_TYPE_STDSTRING, &fileName,  " label='File Name' ");
  TwAddButton(systemInterface,"savebn", saveFileButton, NULL, " label='Save Scenario' ");
  TwAddButton(systemInterface,"loadbn", loadFileButton, NULL, " label='Load Scenario' ");
}
void interface::setupDialog() {

}

// Class External Callbacks
void TW_CALL saveFileButton(void *) {
  std::cerr << "Saving File: " << std::endl;
}

void TW_CALL loadFileButton(void *) {
  std::cerr << "Loading File: " << std::endl;
}

void TW_CALL handleFilename(std::string& destinationClientString, const std::string& sourceLibraryString) {
  // Copy the content of souceString handled by the AntTweakBar library
  destinationClientString = sourceLibraryString;

  if(sourceLibraryString == "") {
    destinationClientString = "Default.sav";
  } else {
    for(int itr = destinationClientString.size(); itr > 0; itr--) {
      if(sourceLibraryString[itr] == '.') {
        destinationClientString = destinationClientString.erase(itr, destinationClientString.size());
        itr = 0;
      }
    }
    destinationClientString = destinationClientString+".sav";
  }
}

void TW_CALL deleteBodyButton(void *) {
  std::cerr << "Delete Body: " << std::endl;
}
