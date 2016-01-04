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
  
  simTest.setTimestep(1);
  simTest.setGravConst(0.1);

  double b1Pos[2] = { 0.0, 0.0 };
  double b2Pos[2] = { 100.0, 0.0 };
  double b1Vel[2] = { 0.0, 0.0 };
  double b2Vel[2] = { 0.0, 0.5 };
  // Create Local Bodies - Better Solution Needed
  body bl0(1000, 100, b1Pos, b1Vel);
  body bl1(0.1, 0.1, b2Pos, b2Vel);
  // Pass Pointer - This relies on the sim initialising all bodies prior to loop.
  simTest.newBody(&bl0);
  simTest.newBody(&bl1);

  //while (1) {
  for (int i = 0; i < 200; i++) {
    simTest.itteration();
    simTest.outputTest();
  }
  while(1) {}
}