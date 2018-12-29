#include <array>
#include <vector>
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

const int gw = 32;
const int gh = 32;

//Width and height +1 to make Gradient cover [0, gw], [0, gh]
vector<vector<array<double, 2>>> Gradient(gh + 1, vector<array<double, 2>>(gw + 1, array<double, 2>()));

void genGrad2D()
{
  srand((unsigned)time(NULL));
  for(auto& row : Gradient)
    for(auto& ele : row)
      {
	ele[0] = double(rand() % 256) / 256;
	ele[1] = sqrt(1 - pow(ele[0], 2));
      }
}

// Function to linearly interpolate between a0 and a1
// Weight w should be in the range [0.0, 1.0]
inline float lerp(float a, float b, float w)
{
  return a + w * (b - a);
}

// Computes the dot product of the distance and gradient vectors.
float dotGridGradient(int ix, int iy, float x, float y)
{
  // Compute the distance vector
  float dx = x - (float)ix;
  float dy = y - (float)iy;

  // Compute the dot-product
  return (dx*Gradient[iy][ix][0] + dy*Gradient[iy][ix][1]);
}

// Compute Perlin noise at coordinates x, y
float perlin(float x, float y)
{
  // Determine grid cell coordinates
  int x0 = int(x);
  int x1 = x0 + 1;
  int y0 = int(y);
  int y1 = y0 + 1;

  // Determine interpolation weights
  // Could also use higher order polynomial/s-curve here
  float sx = x - (float)x0;
  float sy = y - (float)y0;

  // Interpolate between grid point gradients
  float n0, n1, avgx1, avgx2, avg;
  n0 = dotGridGradient(x0, y0, x, y);
  n1 = dotGridGradient(x1, y0, x, y);
  avgx1 = lerp(n0, n1, sx);
  n0 = dotGridGradient(x0, y1, x, y);
  n1 = dotGridGradient(x1, y1, x, y);
  avgx2 = lerp(n0, n1, sx);
  avg = lerp(avgx1, avgx2, sy);

  return avg;
}
