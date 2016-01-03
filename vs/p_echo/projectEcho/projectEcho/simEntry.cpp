/*
*| Project Echo Simulation
*| Revision: 0.01
*| Author: Byron Theobald
*/

#include "simEntry.h"

void simInit() {
  sim_obj simTest;
  float Col[3] = { 1.0f, 1.0f, 1.0f };
  double b1Pos[2] = { 0.0, 0.0 };
  double b2Pos[2] = { 100.0, 0.0 };
  double b2Vel[2] = { 0.0, 1.0001 };
  simTest.newBody(body(1000.0, 10.0, Col, true, b1Pos));
  simTest.newBody(body(0.1, 0.1, Col, b1Pos, b2Vel));

  while (1) {
    simTest.itteration();
    simTest.OutputTest();
  }
}