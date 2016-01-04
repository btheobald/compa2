/*
*| Project Echo Simulation
*| Revision: 0.01
*| Author: Byron Theobald
*/

#include "simEntry.h"
#include "body.h"
#include <iostream>
using namespace std;

void simInit() {
  sim_obj simTest;
  
  simTest.setTimestep(0.1);
  simTest.setGravConst(0.1);

  double b0Pos[2] = { 0.0, 0.0 };
  double b1Pos[2] = { 1000.0, 0.0 };
  double b2Pos[2] = { 1001.0, 0.0 };

  double b0Vel[2] = { 0.0, 0.0 };
  double b1Vel[2] = { 0.0, 0.5 };
  double b2Vel[2] = { 0.0, 0.05 };
  // Create Local Bodies - Better Solution Needed
  body bl0(1000, 100, b0Pos, b0Vel);
  body bl1(0.1, 0.1, b1Pos, b1Vel);
  body bl2(0.01, 0.01, b2Pos, b2Vel);
  // Pass Pointer - This relies on the sim initialising all bodies prior to loop.
  //simTest.newBody(&bl0);
  simTest.newBody(&bl1);
  simTest.newBody(&bl2);

  //while (1) {
  for (int i = 0; i < 1000; i++) {
    simTest.itteration();
    simTest.outputTest();
  }
}