#include "image_utility.h"
#include "primitives.h"
#include <functional>
#include <cmath>
#include <iostream>
#include <GL/glut.h>

//This is a table dealing with Flipping transformations
std::function<Point(Point)> lineTrans[4] =
  {
    [](Point p){return p;},
    [](Point p){return Point(p.x, -p.y);},
    [](Point p){return Point(p.y, p.x);},
    [](Point p){return Point(p.y, -p.x);}
  };

void drawLine(Point p1, Point p2)
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
  glBegin(GL_POINTS);
  for(int x = p1.x, y = p1.y; x <= p2.x; ++x)
    {
      setPixel(lineTrans[transIdx](Point(x, y)));
      
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
  glEnd();
}

void drawCircle(Point center, int r)
{
  int p = 1 - r;

  glBegin(GL_POINTS);
  for(int x = 0, y = r; x <= y; ++x)
    {
      setOctPixel(Point(x, y), center);

      if(p < 0)
	p += 2 * x + 3;
      else
	{
	  p += 2 * (x - y) + 5;
	  --y;
	}
    }
  glEnd();
}


void drawElipse(Point center, int rx, int ry)
{
  //Some frequently used constants
  int rx2 = rx * rx;
  int ry2 = ry * ry;
  int tworx2 = 2 * rx2;
  int twory2 = 2 * ry2;
  int threery2 = 3 * ry2;
  int threerx2 = 3 * rx2;
  
  int dx = 0;
  int dy = tworx2 * ry;
  int p;
  
  //abs(slope) < 1
  int x = 0;
  int y = ry;
  p = round(ry2 - rx2 * ry + 0.25 * rx2);

  glBegin(GL_POINTS);
  for(; dx < dy; ++x)
    {
      setQuartPixel(Point(x, y), center);
      
      if(p < 0)
	p += dx + threery2;
      else
	{
	  p += dx + threery2 + tworx2 - dy;
	  --y;
	  dy -= tworx2;
	}

      dx += twory2;
    }
  glEnd();
}

void drawEntity(const Entity& ent)
{
  glColor3fv(ent.color);
  
  for(const Entity::Edge& e : ent.edges)
    drawLine(ent.verts[e.first], ent.verts[e.second]);

  for(const Entity::Circle& c : ent.circles)
    drawCircle(ent.verts[c.first], c.second);
}
