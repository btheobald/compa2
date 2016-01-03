/*
*| Project Echo Simulation
*| Revision: 0.01
*| Author: Byron Theobald
*/

#include "simEntry.h"
#include <iostream>
using namespace std;

void simInit() {
  sim_obj simTest;
  double b1Pos[2] = { 0.0, 0.0 };
  double b2Pos[2] = { 100.0, 0.0 };
  double b1Vel[2] = { 0.0, 0.0 };
  double b2Vel[2] = { 0.0, 1.0001 };
  simTest.newBody(1000, 100, b1Pos, b1Vel);
  simTest.newBody(0.1, 0.1, b2Pos, b2Vel);

  while (1) {
    simTest.itteration();
    simTest.outputTest();
  }
}