// Header Include
#include "rdr_obj.hpp"

#define TEST_BODIES 1000
#define RADIUS 5000

void rdr_obj::setupDefaultScenario() {
  // Simulation Control
  UGC = 0.1;
  IDT = 0.01;
  IPF = 1;

  // Create a Pseudo-random circular distribution of bodies around 0,0
  // Temporary Variables

  // Use Mersenne Twister for RNE, range 0 - 800.
  std::uniform_real_distribution<> pos(0, RADIUS);
  std::random_device r;
  std::mt19937 gen(r());
  double tempRand, tempCirX, tempCirY, tempDist, tempVelX, tempVelY;
  for(int bIDC = 0; bIDC < TEST_BODIES; bIDC++) {
    // Ensure that bodies are not too close to center.
    do tempRand = pos(gen) - RADIUS/2; while((tempRand < 40) & (tempRand > -40));

    // Map to Circle
    tempCirX = (tempRand * cos(2 * M_PI * tempRand));
    tempCirY = (tempRand * sin(2 * M_PI * tempRand)); // Squash in Y
    // Calculate Distance to 0,0
    tempDist = sqrt(pow(tempCirX,2) + pow(tempCirY,2));
    // Calc Velocity
    tempVelY = copysign(sqrt((UGC*100000) / pow(tempDist,3)) * tempCirX, tempCirX);
    tempVelX = copysign(sqrt((UGC*100000) / pow(tempDist,3)) * tempCirY, -tempCirY);

    newBody(0.01, 1, tempCirX, tempCirY, tempVelX, tempVelY);
  }
  // Add Massive Central Body
  newBody(100000, 10, 0, 0, 0, 0);
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
