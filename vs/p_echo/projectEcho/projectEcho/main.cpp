#include <iostream>
using namespace std;

void DrawCircle(float cx, float cy, float r, int num_segments);

int main() {
  float testValueCentre = 9.9E11;
  
  cout.precision(20);
  DrawCircle(testValueCentre, testValueCentre, 1186000.0, 16);


  while (1) {

  }

  return 0;
}

void DrawCircle(float cx, float cy, float r, int num_segments)
{
  float theta = 2 * 3.1415926 / float(num_segments);
  float tangetial_factor = tanf(theta);//calculate the tangential factor 

  float radial_factor = cosf(theta);//calculate the radial factor 

  float x = r;//we start at angle = 0 

  float y = 0;

  for (int ii = 0; ii < num_segments; ii++)
  {
    cout << x + cx << " " << y + cy << endl;//output vertex 

                               //calculate the tangential vector 
                               //remember, the radial vector is (x, y) 
                               //to get the tangential vector we flip those coordinates and negate one of them 

    float tx = -y;
    float ty = x;

    //add the tangential vector 

    x += tx * tangetial_factor;
    y += ty * tangetial_factor;

    //correct using the radial factor 

    x *= radial_factor;
    y *= radial_factor;
  }
}