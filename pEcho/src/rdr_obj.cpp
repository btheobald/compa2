// Header Include
#include "rdr_obj.hpp"

#define BODIES 300
#define RADIUS 500
#define SPACING 50

void rdr_obj::setupDefaultScenario() {
  // Simulation Control
  UGC = 1;
  IDT = 0.01;
  IPF = 1;

  // Create a Pseudo-random circular distribution of bodies around 0,0
  // Temporary Variables

  // Use Mersenne Twister for RNE, range 0 - 800.
  std::uniform_real_distribution<> pos(0, RADIUS*2);
  std::random_device r;
  std::mt19937 gen(r());
  double tempRand, tempCirX, tempCirY, tempDist, tempVelX, tempVelY;
  // Add Massive Central Body
  newBody(100000, 10, 0, 0, 0, 0);
  for(int bIDC = 0; bIDC < BODIES; bIDC++) {
    // Ensure that bodies are not too close to center.
    do tempRand = pos(gen) - RADIUS/2; while((tempRand < SPACING) & (tempRand > -SPACING));

    // Map to Circle
    tempCirX = bodyStore[0].getPosition(0)+(tempRand * cos(2 * M_PI * tempRand));
    tempCirY = bodyStore[0].getPosition(1)+(tempRand * sin(2 * M_PI * tempRand));

    // Calculate Distance to Body
    tempDist = sqrt(pow(bodyStore[0].getPosition(0)-tempCirX,2) + pow(bodyStore[0].getPosition(1)-tempCirY,2));

    // Calc Velocity
    tempVelY = copysign(sqrt((UGC*100000) / pow(tempDist,3)) * tempCirX, tempCirX);
    tempVelX = copysign(sqrt((UGC*100000) / pow(tempDist,3)) * tempCirY, -tempCirY);

    newBody(0.01, 1, tempCirX, tempCirY, tempVelX, tempVelY);
  }

  newBody(100000, 10, 1500, 0, 0, 1);
  for(int bIDC = 0; bIDC < BODIES; bIDC++) {
    // Ensure that bodies are not too close to center.
    do tempRand = pos(gen) - RADIUS/2; while((tempRand < SPACING) & (tempRand > -SPACING));

    // Map to Circle
    tempCirX = bodyStore[301].getPosition(0)+(tempRand * cos(2 * M_PI * tempRand));
    tempCirY = bodyStore[301].getPosition(1)+(tempRand * sin(2 * M_PI * tempRand));

    // Calculate Distance to Body
    tempDist = sqrt(pow(bodyStore[301].getPosition(0)-tempCirX,2) + pow(bodyStore[301].getPosition(1)-tempCirY,2));

    // Calc Velocity
    tempVelY = copysign(sqrt((UGC*100000) / pow(tempDist,3)) * (tempCirX-bodyStore[301].getPosition(0)), (tempCirX-bodyStore[301].getPosition(0)));
    tempVelX = copysign(sqrt((UGC*100000) / pow(tempDist,3)) * (tempCirY-bodyStore[301].getPosition(1)), -(tempCirY-bodyStore[301].getPosition(1)));

    newBody(0.01, 1, tempCirX, tempCirY, tempVelX, tempVelY);
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
