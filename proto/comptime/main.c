#include <stdio.h>
#include <math.h>
#include <time.h>

#define GRAVCONST 1

typedef int bodyMatrix[2]; // 0:x 1:y
typedef struct {
  bodyMatrix bodyPosition;
  double bodyMass;
} bodyData;

double calc_d(bodyData body1, bodyData body2, int dir); // Calculate Distance
double grav_t(bodyData body1, bodyData body2); // Traditional Gravitational Law
double findAngle(bodyData body1, bodyData body2); // Find Angle
double getComp(double force, double angle, int dir); // Find Components
double grav_v(bodyData body1, bodyData body2, int dir); // Vector Gravitational Law

double trad(bodyData body1, bodyData body2);
double vect(bodyData body1, bodyData body2);

int main(void) {
  
  double t_Angle = 0, t_Force = 0, t_Fx = 0, t_Fy = 0; 
  double v_Fx = 0, v_Fy = 0; 

  bodyData body1, body2;
  // B1, Pos = (1,1)
  body1.bodyMass = 1;
  body1.bodyPosition[0] = 1;
  body1.bodyPosition[1] = 2;
  // B2, Pos = (1,1)
  body2.bodyMass = 1;
  body2.bodyPosition[0] = 4;
  body2.bodyPosition[1] = 6;
  
  for(int id = 0; id < 10; id++) {
    
    
  }
  
  for(int id = 0; id < 10; id++) {
  
  }
  
  return 0;
}

// Calculate Distance - dir 0 = x, 1 = y, 2 = vector
double calc_d(bodyData body1, bodyData body2, int dir) {
  double vector, x, y;
  
  x = body2.bodyPosition[0] - body1.bodyPosition[0];
  y = body2.bodyPosition[1] - body1.bodyPosition[1];
  
  vector = sqrt((x*x) + (y*y));
  
  switch(dir) {
    case 0 : return x; break;
    case 1 : return y; break;
    case 2 : return vector; break;
  }
}

// Traditional Gravitational Law
double grav_t(bodyData body1, bodyData body2) {
  double result, dist;
  // Get Distance
  dist = calc_d(body1, body2, 2);
  // Get Force
  result = (GRAVCONST*body1.bodyMass*body2.bodyMass)/pow(dist,2);
  return result;
}

// Find Angle
double findAngle(bodyData body1, bodyData body2) {
  return atan(calc_d(body1, body2, 1) / calc_d(body1, body2, 0));
}

// Find Component - dir 0 = x, 1 = y
double getComp(double force, double angle, int dir) {
  double result;
  
  switch(dir) {
    case 0 : // x
      result = force*cos(angle);
      break;
    case 1 : // y
      result = force*sin(angle);
      break;
  }
  return result;
}

// Vector Gravitational Law - dir 0 = x, 1 = y
double grav_v(bodyData body1, bodyData body2, int dir) {
  double result, dist;
  // Get Distance
  dist = calc_d(body1, body2, 2);
  // Get Force
  result = (GRAVCONST*body1.bodyMass*body2.bodyMass)/pow(dist,3);
  
  switch(dir) {
    case 0 : // x;
      result *= calc_d(body1, body2, 0);
      break;
    case 1 : // y;
      result *= calc_d(body1, body2, 1);
      break;
  }
  
  return result;
}

double trad(bodyData body1, bodyData body2) {
  clock_t begin, end;
  double t_Time;
  
  // Begin Timer
  begin = clock();
  
  // Traditional
  t_Force = grav_t(body1, body2);
  t_Angle = findAngle(body1, body2);
  t_Fx = getComp(t_Force, t_Angle, 0);
  t_Fy = getComp(t_Force, t_Angle, 1);
  
  // End Timer
  end = clock();
  t_Time = (double)(end - begin);
  
  // Print Results
  printf("TT: %g | ", t_Time);
  timeStore[id][0] = t_Time;
  
  return t_Time;
}

double vect(bodyData body1, bodyData body2) {
  clock_t begin, end;
  double v_Time;
  
  // Begin Timer
  begin = clock();
  
  // Vector
  // Get Force Components
  v_Fx = grav_v(body1, body2, 0);
  v_Fy = grav_v(body1, body2, 1);
  
  // End Timer
  end = clock();
  v_Time = (double)(end - begin);
  
  // Print Results
  printf("VT: %g\n", v_Time);
  
  timeStore[id][1] = v_Time;
  
  return v_Time;
}
