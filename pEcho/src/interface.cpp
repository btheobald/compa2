#include "interface.hpp"

interface::interface(int p_wXRes, int p_wYRes, rdr_obj* p_renderAccess) {
  renderAccess = p_renderAccess;

  // Init AntTweakBar
  TwInit(TW_OPENGL, NULL);
  TwWindowSize(p_wXRes, p_wYRes);

  simInterface = TwNewBar("Simulation");
  bodyInterface = TwNewBar("Body");
  systemInterface = TwNewBar("System");

  setupSimInterface();
  setupBodyInterface(0);
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
  TwDefine(" 'Simulation' refresh=0.01");

  // Control
  TwAddVarRW(simInterface, "ugcvar", TW_TYPE_DOUBLE,  &UGC_I,        " min=1E-12  max=10   step=0.01  precision=7   label='Gravitational Constant'  group=Control ");
  TwAddVarRW(simInterface, "idtvar", TW_TYPE_DOUBLE,  &IDT_I,        " max=-1E9   max=1E15  step=0.01  precision=7   label='Itteration Delta Time'   group=Control ");
  TwAddVarRW(simInterface, "collid", TW_TYPE_BOOLCPP, &doCollisions_I,"true=On      false=Off                       label='Simulate Collisions'     group=Control ");
  // Runtime
  TwAddVarRW(simInterface, "paused", TW_TYPE_BOOLCPP, &paused_I,     " true=Paused  false=Running                   label='Run/Pause'               group=Runtime ");
  TwAddVarRW(simInterface, "ipfvar", TW_TYPE_INT32,   &IPF_I,        " min=1      max=10000  step=1                 label='Itterations Per Frame'   group=Runtime ");
  // Statistics
  TwAddVarRO(simInterface, "numbod", TW_TYPE_INT32,   &numBodies_I,  "                                              label='Number of Bodies'        group=Statistics ");
}
void interface::setupBodyInterface(int p_abID) {
  // Color
  TwDefine(" 'Body' color='255 255 255' alpha=150 text=dark");

  // Size
  TwDefine(" 'Body' size='300 330'");
  TwDefine(" 'Body' position='0 182'");
  TwDefine(" 'Body' resizable=false ");
  TwDefine(" 'Body' valueswidth=100 ");
  TwDefine(" 'Body' movable=false");
  TwDefine(" 'Body' refresh=0.01");

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

  TwAddButton(bodyInterface,"delbody", deleteBodyButton, this, " label='Delete Body' ");
}
void interface::setupSystemInterface() {
  // Color
  TwDefine(" 'System' color='255 255 255' alpha=150 text=dark");

  // Size
  TwDefine(" 'System' size='300 90'");
  TwDefine(" 'System' position='0 514'");
  TwDefine(" 'System' resizable=false ");
  TwDefine(" 'System' valueswidth=100 ");
  TwDefine(" 'System' movable=false");
  TwDefine(" 'System' refresh=0.01");

  TwCopyStdStringToClientFunc(handleFilename);
  TwAddVarRW(systemInterface, "filenm", TW_TYPE_STDSTRING, &fileName,  " label='File Name' ");
  TwAddButton(systemInterface,"savebn", saveFileButton, this, " label='Save Scenario' ");
  TwAddButton(systemInterface,"loadbn", loadFileButton, this, " label='Load Scenario' ");
}

void interface::setupDialog() {

}

void interface::updateControl(rdr_obj* localScenario) {
  localScenario->updateLocalControl(UGC_I, IDT_I, IPF_I, doCollisions_I);
}

void interface::updateScenario(rdr_obj* localScenario) {
  body* bodyPointer = localScenario->getBodyPointer(abID_I);

  bodyPointer->setMass(abMass_I);
  bodyPointer->setRadius(abRadius_I);
  bodyPointer->setFixed(abFixed_I);
  bodyPointer->setColor(abColor_I);

  bodyPointer->setPosition(abPositionX_I, 0);
  bodyPointer->setPosition(abPositionY_I, 1);

  bodyPointer->setVelocity(abVelocityX_I, 0);
  bodyPointer->setVelocity(abVelocityY_I, 1);
}

void interface::updateInterface(rdr_obj* localScenario) {
  // Update Sim Variables
  UGC_I = localScenario->getUGC();
  IDT_I = localScenario->getIDT();
  IPF_I = localScenario->getIPF();
  numBodies_I = localScenario->getCurrentBodies();

  // Update Body Interface
  body* bodyPointer = localScenario->getBodyPointer(abID_I);

  abMass_I = bodyPointer->getMass();
  abRadius_I = bodyPointer->getRadius();
  abFixed_I = bodyPointer->getFixedStatus();
  abColor_I[0] = bodyPointer->getColor(0);
  abColor_I[1] = bodyPointer->getColor(1);
  abColor_I[2] = bodyPointer->getColor(2);

  abPositionX_I = bodyPointer->getPosition(0);
  abPositionY_I = bodyPointer->getPosition(1);

  abVelocityX_I = bodyPointer->getVelocity(0);
  abVelocityY_I = bodyPointer->getVelocity(1);

  abForceX_I = bodyPointer->getForce(0);
  abForceY_I = bodyPointer->getForce(1);

  abAccelerationX_I = bodyPointer->getAcceleration(0);
  abAccelerationY_I = bodyPointer->getAcceleration(1);
}

void interface::updateActiveID(int p_bodyID) {
  if(p_bodyID != -1) abID_I = p_bodyID;
}

// Class External Callbacks
void TW_CALL saveFileButton(void *cData) {
  interface *iface = static_cast<interface*>(cData); // scene pointer is stored in clientData
  std::cerr << "Saving File: " << iface->fileName << std::endl;
}

void TW_CALL loadFileButton(void *cData) {
  interface *iface = static_cast<interface*>(cData); // scene pointer is stored in clientData
  std::cerr << "Loading File: " << iface->fileName << std::endl;
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

void TW_CALL deleteBodyButton(void *cData) {
  interface *iface = static_cast<interface*>(cData);
  delete(iface->renderAccess->getBodyPointer(iface->abID_I));
  iface->renderAccess->delBody(iface->abID_I-1);
  iface->updateInterface(iface->renderAccess);
}

void TW_CALL newBodyButton(void *cData) {

}

void TW_CALL newSuperStructureButton(void *cData) {

}
