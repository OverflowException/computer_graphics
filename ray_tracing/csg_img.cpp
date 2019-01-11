#include <unistd.h>
#include <iostream>
#include <cmath>
#include <random>
#include <sstream>
#include <vector>
#include "bmp_writer.h"

#define TWO_PI 6.28318530718f
#define N 64
#define MAX_STEP 10
#define MAX_DISTANCE 500
#define EPSILON 1e-6f

int width = 640;
int height = 480;
int radius = 50;

std::vector<std::vector<Color>> canvas(height, std::vector<Color>(width, Color(0, 0, 0)));

struct Circle
{
  float x;
  float y;
  float radius;
  float emission;
};

std::vector<Circle> circles;

struct Result
{
  float sd;
  float emission;
};

//Calculate Singned Distance Field of a circle
inline float circleSDF(float x, float y, float cx, float cy, float r)
{
  return sqrt(pow(cx - x, 2) + pow(cy - y, 2)) - r;
}

Result unionOp(Result a, Result b)
{
  return a.sd < b.sd ? a : b;
}

Result intersectOp(Result a, Result b)
{
  Result r = a.sd > b.sd ? b : a;
  r.sd = a.sd > b.sd ? a.sd : b.sd;
  return r;
}

Result subtractOp(Result a, Result b)
{
  Result r = a;
  r.sd = (a.sd > -b.sd) ? a.sd : -b.sd;
  return r;
}

Result scene(float x, float y)
{
  Result r = {circleSDF(x, y, circles[0].x, circles[0].y, circles[0].radius), circles[0].emission};
  for(int idx = 1; idx < circles.size(); ++idx)
    r = unionOp(r,
		{circleSDF(x, y, circles[idx].x, circles[idx].y, circles[idx].radius), circles[idx].emission});
  
  return r;
}   

//Ray marching method of ray tracing
float trace(float ox, float oy, float dx, float dy)
{
  float t;
  for(int i = 0; i < MAX_STEP && t < MAX_DISTANCE; ++i)
    {
      Result r = scene(ox + dx * t, oy + dy * t);
      if(r.sd < EPSILON)
	return r.emission;
      t += r.sd;
    }

  return 0;
}

//Direction sampling
float sample(float x, float y)
{
  float sum = 0;
  for(int i = 0; i < N; ++i)
    {
      //Jittered sampling
      float a = TWO_PI * (i + (float)std::rand() / RAND_MAX) / N;
      sum += trace(x, y, cos(a), sin(a));
    }
  return sum / N;
}

int main(int argc, char** argv)
{
  if(argc <= 2 || (argc - 2) % 4 != 0)
    {
      std::cout << "Usage: " << argv[0] << "[filename] [circle data]" << std::endl;
      std::cout << "circle data :" << "[x, y, radius, emission]" << std::endl;
      return 0;
    }

  //Get all circle data
  circles.resize((argc - 2) / 4);
  std::istringstream iss;
  for(int argidx = 2, cidx = 0; cidx < circles.size(); ++cidx)
    {
      iss.clear();
      iss.str(std::string(argv[argidx++]));
      iss >> circles[cidx].x;
      
      iss.clear();
      iss.str(std::string(argv[argidx++]));
      iss >> circles[cidx].y;

      iss.clear();
      iss.str(std::string(argv[argidx++]));
      iss >> circles[cidx].radius;
      
      iss.clear();
      iss.str(std::string(argv[argidx++]));
      iss >> circles[cidx].emission;
    }

  
  float illumi;
  //Generate one frame on canvas
  for(int x = 0; x < width; ++x)
    for(int y = 0; y < height; ++y)
      {
	illumi = sample(x, y);
	illumi *= 255;
	//std::cout << illumi << std::endl;
	canvas[y][x] = Color(illumi, illumi, illumi);
      }

  //Save bmp
  write_bmp(argv[1], 72, canvas);  
  
}
