// Header Include
#include "rdr_obj.hpp"

void rdr_obj::setupDefaultScenario() {
  UGC = 0.1;
  IDT = 0.1;
  IPF = 1;
  // Realistic Size Superstructure
  //createSuperstructure(10, 1.989E30, 5E24, 696000000, 6371000, 0, 0, 0, 0, 5E10, 2E11, com::white);
  // Small Galaxy
  //createSuperstructure(1000, 1.989E30, 5E24, 696000000, 6371000, 0, 0, 0, 0, 5E10, 1E24, com::white);

  // Small Galaxy
  createSuperstructure(10, 10000, 0.1, 10, 0.1, 0, 0, 0, 0, 100.0, 500.0, com::white);

  /*/// Grid
  for(int x = -100; x <= 100; x++) {
    for(int y = -100; y <= 100; y++) {
      if((x==0) & (y==0)) {
        newBody(0.001, 1, x*10, y*10, 0, 0, com::red);
      } else {
        newBody(0.001, 1, x*10, y*10, 0, 0, com::white);
      }
    }
  }*/

  // Precessing Orbits
  //newBody(10000, 10,  100, 0, 0,  1.6, com::white);
  //newBody(10000, 10, -100, 0, 0, -1.6 , com::white);

  // Sun Earth Moon System
  //newBody(1000, 10, 0, 0, 0, 0, com::red);
  //newBody(0.1, 1, 1000, 0, 0, 0.316, com::green);
  //newBody(0.001, 0.5, 1000, 10, 0.0317, 0.316, com::white);

  //newBody(1, 10,  200, 0, 0, 0, com::white);
  //newBody(1, 10, -200, 0, 0, 0, com::white);
  //newBody(0.001, 1, 0, 100, 0, 0, com::white);
  //newBody(0.001, 1, 150, 150, 0, 0, com::white);
  //newBody(p_cMass, p_cRadius, p_cPosX, p_cPosY, p_cVelX, p_cVelY, p_Color);
}

void rdr_obj::createSuperstructure(int p_soBodies, double p_cMass, double p_oMass, double p_cRadius, double p_oRadius, double p_cPosX, double p_cPosY, double p_cVelX, double p_cVelY, double p_coSpacing, double p_sRadius, const float p_Color[3]) {
  // Create a Pseudo-random circular distribution of bodies around a central body.

  // Use Mersenne Twister for RNE within range.
  std::uniform_real_distribution<> pos(0, p_sRadius*2);
   // Use random device for seed value
  //std::random_device r;
  //std::mt19937 gen(r());
  std::mt19937 gen;


  // Temporary Variables
  double tempRand, tempCirX, tempCirY, tempDist, tempVelX, tempVelY;
  // Add Central Body
  newBody(p_cMass, p_cRadius, p_cPosX, p_cPosY, p_cVelX, p_cVelY, p_Color);
  //int bodyOffset = bodyStore.size() - 1;
  for(int bIDC = 0; bIDC < p_soBodies; bIDC++) {
    // Ensure that bodies are not too close to center.
    do tempRand = pos(gen) - p_sRadius; while((tempRand < p_coSpacing) & (tempRand > -p_coSpacing));

    // Map to Circle
    tempCirX = p_cPosX+(tempRand * cos(2 * M_PI * tempRand));
    tempCirY = p_cPosY+(tempRand * sin(2 * M_PI * tempRand));

    // Calculate Distance to Body
    tempDist = sqrt(pow(p_cPosX-tempCirX,2) + pow(p_cPosY-tempCirY,2));

    // Calc Velocity
    tempVelX = copysign(sqrt((UGC*(p_cMass+p_oMass)) / pow(tempDist,3)) * (tempCirY-p_cPosY), (tempCirY-p_cPosY)) + p_cVelX;
    tempVelY = copysign(sqrt((UGC*(p_cMass+p_oMass)) / pow(tempDist,3)) * (tempCirX-p_cPosX), -(tempCirX-p_cPosX)) + p_cVelY;

    newBody(p_oMass, p_oRadius, tempCirX, tempCirY, tempVelX, tempVelY, p_Color);
  }
}

void rdr_obj::updateSharedArea(sharedStage* l_sharedDataAccess) {
  // Push Body Data To Shared
  l_sharedDataAccess->populateBodyStore_R(returnBodyStore());
  l_sharedDataAccess->populateBodyStore_S(returnBodyStore());
  // Push Simulation Control To Shared
  l_sharedDataAccess->setUGC(UGC);
  l_sharedDataAccess->setIDT(IDT);
  l_sharedDataAccess->setIPF(IPF);
  // Unpause Sim
  l_sharedDataAccess->setStatus(0, false);
}

void rdr_obj::updateLocalStore(sharedStage* l_sharedDataAccess) {
  // Push Body Data To Shared
  if(l_sharedDataAccess->newSScenarioCheck()) {
    populateBodyStore(l_sharedDataAccess->returnBodyStore_S());
    l_sharedDataAccess->simWait.notify_all();
  }
  // Skip if No New Data Avaliable
}

void rdr_obj::drawBody(int bodyID) {
  const int segments = 64;

  double posX = bodyStore[bodyID].getPosition(0);
  double posY = bodyStore[bodyID].getPosition(1);
  double radius = bodyStore[bodyID].getRadius();

  // Precalc
  float theta = 2 * M_PI / segments;

  // Factors
  float tanFact = tan(theta);
  float radFact = cos(theta);

  float x = radius;
  float y = 0;

  // Plot Minimum Point.
  glColor3f(bodyStore[bodyID].getColor(0), bodyStore[bodyID].getColor(1), bodyStore[bodyID].getColor(2));
  glBegin(GL_POINTS);
  glVertex2f(posX, posY);
  glEnd();

  // Plot Real Size
  glBegin(GL_POLYGON);
  for(int i = 0; i < segments; i++) {
    // Output Vertex
    glColor3f(bodyStore[bodyID].getColor(0), bodyStore[bodyID].getColor(1), bodyStore[bodyID].getColor(2));
    glVertex2f(x + posX, y + posY);

    // Copy previous coordinates
    float lx = -y;
    float ly =  x;

    // Calculate Next Vertex
    x += lx * tanFact;
    y += ly * tanFact;

    x *= radFact;
    y *= radFact;
  }
  glEnd();
}

void rdr_obj::drawScene() {
  // Draw Bodies
  for(unsigned int bIDC = 0; bIDC < bodyStore.size(); bIDC++) {
    drawBody(bIDC);
  }
}

int rdr_obj::checkCoord(double x, double y) {
  for(unsigned int bIDC = 0; bIDC < bodyStore.size(); bIDC++) {
    if(((x < bodyStore[bIDC].getPosition(0)+(bodyStore[bIDC].getRadius()+5))   &
        (x > bodyStore[bIDC].getPosition(0)-(bodyStore[bIDC].getRadius()+5)))  &
       ((y < bodyStore[bIDC].getPosition(1)+(bodyStore[bIDC].getRadius()+5))   &
        (y > bodyStore[bIDC].getPosition(1)-(bodyStore[bIDC].getRadius()+5)))) {
      return bIDC;
    }
  }
  return -1;
}

// WARNING : BREAKS ENCAPSULATION
body* rdr_obj::getBodyPointer(int bodyID) {
  return &bodyStore[bodyID];
}
