#include "image_utility.h"
#include "primitives.h"
#include <functional>

//This is a table dealing with Flipping transformations
std::function<Point(Point)> lineTrans[4] =
  {
    [](Point p){return p;},
    [](Point p){return Point(p.x, -p.y);},
    [](Point p){return Point(p.y, p.x);},
    [](Point p){return Point(p.y, -p.x);}
  };

void drawLine(Point p1, Point p2, Image& im, char c)
{  
  //Make sure p1 is on the left, p2 is on the right
  if(p1.x > p2.x)
    std::swap(p1, p2);
  
  int dy = p2.y - p1.y;
  int dx = p2.x - p1.x;

  int transIdx = 0;
    
  //All of the following transformation will not affct the left-right relative position of p1 and p2

  //Slope is negative, flip along X axis
  if(dy < 0)
    {
      p1.y = -p1.y;
      p2.y = -p2.y;
      dy = -dy;

      transIdx |= 0x01;
    }
  
  //abs(slope) > 1, flip along y=x axis
  if(abs(dy) > dx)
    {
      std::swap(p1.x, p1.y);
      std::swap(p2.x, p2.y);
      std::swap(dx, dy);

      transIdx |= 0x02;
    }
  
  int alpha, beta, criterion;
  
  //Initialize constants and criterion for iteration
  alpha = 2 * dy;
  beta = 2 * dy - 2 * dx;
  criterion = 2 * dy - dx;

  //Draw each pixel  
  for(int x = p1.x, y = p1.y; x <= p2.x; ++x)
    {
      setPixel(lineTrans[transIdx](Point(x, y)), im, c);
      
      //Nearer to upper
      if(criterion > 0)
	{
	  ++y;
	  criterion += beta;
	}
      //Nearer to lower
      else
	criterion += alpha;
    }
  //One last point
  //setPixel(lineTrans[transIdx](p2), im, c);
}

void drawCircle(Point center, int radius, Image& im, char c)
{
  int p = 1 - radius;
  
  for(int x = 0, y = radius; x <= y; ++x)
    {
      setOctPixel(Point(x, y), center, im, c);

      if(p < 0)
	p += 2 * x + 3;
      else
	{
	  p += 2 * (x - y) + 5;
	  --y;
	}
    }
}
