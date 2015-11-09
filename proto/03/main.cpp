#include <iostream>
#include <cmath>

#define TIMEBASE 0.01
using namespace std;

int main() {
  double position_r[2], velocity[2], acceleration[2];
  double deltat = 0.0001;
  double itterations = 100000;
  position_r[0] = 1;
  position_r[1] = 0;
  
  velocity[0] = 0;
  velocity[1] = 0.5;

  for (int ns = 0; ns < itterations; ns++) {
    double r2 = position_r[0]*position_r[0] + position_r[1]*position_r[1];
   
    deltat = (TIMEBASE * r2/100);
    
    if(deltat < 0.00001) {
      itterations++;
    }
    
    for (int k = 0; k < 2; k++) {
      acceleration[k] = - position_r[k] / (r2 * sqrt(r2));
    }
    for (int k = 0; k < 2; k++) {
      position_r[k] += velocity[k] * deltat;
      velocity[k] += acceleration[k] * deltat;
    }
    
    cout << position_r[0] << " " << position_r[1] << endl;
  }
}
