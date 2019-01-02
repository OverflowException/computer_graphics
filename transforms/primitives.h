#ifndef _PRIMITIVES_H
#define _PRIMITIVES_H

#include "object_utility.h"
#include "display_utility.h"
#include <functional>
#include <cmath>
#include <GL/glut.h>

//This is a table dealing with Flipping transformations
std::function<Pointi(Pointi)> lineTrans[4] =
  {
    [](Pointi p){return p;},
    [](Pointi p){return Pointi(p.x, -p.y);},
    [](Pointi p){return Pointi(p.y, p.x);},
    [](Pointi p){return Pointi(p.y, -p.x);}
  };

template<typename Point>
void drawLine(Point p1, Point p2)
{
  Pointi pi1(p1);
  Pointi pi2(p2);
  
  //Make sure pi1 is on the left, pi2 is on the right
  if(pi1.x > pi2.x)
    std::swap(pi1, pi2);
  
  int dy = pi2.y - pi1.y;
  int dx = pi2.x - pi1.x;

  int transIdx = 0;
    
  //All of the following transformation will not affct the left-right relative position of pi1 and pi2

  //Slope is negative, flip along X axis
  if(dy < 0)
    {
      pi1.y = -pi1.y;
      pi2.y = -pi2.y;
      dy = -dy;

      transIdx |= 0x01;
    }
  
  //abs(slope) > 1, flip along y=x axis
  if(abs(dy) > dx)
    {
      std::swap(pi1.x, pi1.y);
      std::swap(pi2.x, pi2.y);
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
  for(int x = pi1.x, y = pi1.y; x <= pi2.x; ++x)
    {
      setPixel(lineTrans[transIdx](Pointi(x, y)));
      
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

template<typename Point, typename Tr>
void drawCircle(Point center, Tr r)
{
  Pointi centeri(center);
  int p = 1 - round(r);

  glBegin(GL_POINTS);
  for(int x = 0, y = r; x <= y; ++x)
    {
      setOctPixel(Pointi(x, y), centeri);

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

template<typename Point, typename Tr>
void drawElipse(Point center, Tr rx, Tr ry)
{
  Pointi centeri(center);
  int rxi = round(rx);
  int ryi = round(ry);
  
  //Some frequently used constants
  int rx2 = rxi * rxi;
  int ry2 = ryi * ryi;
  int tworx2 = 2 * rx2;
  int twory2 = 2 * ry2;
  int threery2 = 3 * ry2;
  int threerx2 = 3 * rx2;
  
  int dx = 0;
  int dy = tworx2 * ryi;
  int p;
  
  //abs(slope) < 1
  int x = 0;
  int y = ryi;
  p = round(ry2 - rx2 * ryi + 0.25 * rx2);

  glBegin(GL_POINTS);
  for(; dx < dy; ++x)
    {
      setQuartPixel(Pointi(x, y), centeri);
      
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

template<typename Entity>
void drawEntity(const Entity& ent)
{
  glColor3fv(ent.color);
  
  for(const typename Entity::edge_type& e : ent.edges)
    drawLine(ent.verts[e.first], ent.verts[e.second]);

  for(const typename Entity::circle_type& c : ent.circles)
    drawCircle(ent.verts[c.first], c.second);
}


#endif
