#include <iostream>
#include <cmath>
using namespace std;

int main() {
  double r[2], v[2], a[2];
  double dt = 0.00001;
  
  r[0] = 1;
  r[1] = 0;
  
  v[0] = 0;
  v[1] = 0.5;

  for (int ns = 0; ns < 10000000; ns++) {
    double r2 = r[0]*r[0] + r[1]*r[1];
    
    for (int k = 0; k < 2; k++) {
      a[k] = - r[k] / (r2 * sqrt(r2));
    }
    for (int k = 0; k < 2; k++) {
      r[k] += v[k] * dt;
      v[k] += a[k] * dt;
    }
    
    cout << r[0] << " " << r[1] << endl;
  }
}
