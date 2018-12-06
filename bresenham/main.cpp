#include <iostream>
#include <utility>
#include <algorithm>
#include <unistd.h>
#include "image_utility.h"
#include "primitives.h"

Image canvas;

int main(int argc, char** argv)
{
  //Initialize image
  int w = 33;
  int h = 33;
  canvas.resize(h, std::vector<char>(w, ' '));

  Point p0(16, 16);
  Point pArr[16] =
    {
      {30, 15},
      {30, 20},
      {30, 30},
      {20, 30},
      {15, 30},
      {10, 30},
      {0, 30},
      {0, 20},
      {0, 15},
      {0, 10},
      {0, 0},
      {10, 0},
      {15, 0},
      {20, 0},
      {30, 0},
      {30, 10}
    };
  
  for(int idx = 0; ; ++idx)
    {
      idx %= 16;
      
      usleep(500000);
      system("clear");
      
      drawLine(p0, pArr[idx], canvas, '*');
      drawCircle(p0, idx, canvas, '#');
      drawElipse(p0, idx, idx / 2, canvas, '&');
      
      outImage(canvas);
      clearImage(canvas, ' ');
    }
  
  return 0;
}

