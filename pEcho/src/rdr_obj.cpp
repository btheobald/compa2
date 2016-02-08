// Header Include
#include "rdr_obj.hpp"

void rdr_obj::setupDefaultScenario() {
<<<<<<< HEAD
  // Simulation Control
  UGC = 1;
  IDT = 0.1;
  IPF = 1;

  createSuperstructure(1000, 100000, 0.1, 5, 0.7, 500, 200, -3, -2, 50, 250, com::white);
  //newBody(0.001, 1, 0, 0, 0, 0, com::white);
  //newBody(0.001, 1, 100, 0, 0, 0, com::white);
=======
  // Realistic Size ISH
  //createSuperstructure(10, 1.989E30, 5E24, 696000000, 100000000, 0, 0, 0, 0, 1E9, 1E11, com::white);
  // Small Galaxy
  createSuperstructure(1000, 10000, 0.1, 10, 1, 0, 0, 0, 0, 50, 500, com::white);
  //newBody(1, 10,  200, 0, 0, 0, com::white);
  //newBody(1, 10, -200, 0, 0, 0, com::white);
>>>>>>> 4a5a618abaf4e58c0faf489fdea2f4ea2417c070
  //newBody(0.001, 1, 0, 100, 0, 0, com::white);
  //newBody(0.001, 1, 150, 150, 0, 0, com::white);
  //newBody(p_cMass, p_cRadius, p_cPosX, p_cPosY, p_cVelX, p_cVelY, p_Color);
}

void rdr_obj::createSuperstructure(int p_soBodies, double p_cMass, double p_oMass, double p_cRadius, double p_oRadius, double p_cPosX, double p_cPosY, double p_cVelX, double p_cVelY, double p_coSpacing, double p_sRadius, const float p_Color[3]) {
  // Create a Pseudo-random circular distribution of bodies around a central body.

  // Use Mersenne Twister for RNE within range.
  std::uniform_real_distribution<> pos(0, p_sRadius*2);
   // Use random device for seed value
  std::random_device r;
  std::mt19937 gen(r());

  // Temporary Variables
  double tempRand, tempCirX, tempCirY, tempDist, tempVelX, tempVelY;
  // Add Central Body
  newBody(p_cMass, p_cRadius, p_cPosX, p_cPosY, p_cVelX, p_cVelY, p_Color);
  int bodyOffset = bodyStore.size() - 1;
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
  const int segments = 32;

  double posX = bodyStore[bodyID].getPosition(0);
  double posY = bodyStore[bodyID].getPosition(1);
  double radius = bodyStore[bodyID].getRadius();

  // Precalc
  float theta = 2 * 3.1415926 / float(segments);
  // Factors
  float tanFact = tan(theta);
  float radFact = cos(theta);

  float x = radius;
  float y = 0;

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
  for(int bIDC = 0; bIDC < bodyStore.size(); bIDC++) {
    if(((x < bodyStore[bIDC].getPosition(0)+bodyStore[bIDC].getRadius()) & (x > bodyStore[bIDC].getPosition(0)-bodyStore[bIDC].getRadius())) & ((y < bodyStore[bIDC].getPosition(1)+bodyStore[bIDC].getRadius()) & (y > bodyStore[bIDC].getPosition(1)-bodyStore[bIDC].getRadius()))) {
      std::cerr << bIDC << std::endl;
    }
  }
}
