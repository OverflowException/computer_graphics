#ifndef _GEO_H
#define _GEO_H

#include <GL/glut.h>

struct Point
{
  GLdouble x;
  GLdouble y;
  Point(GLdouble _x = 0, GLdouble _y = 0) : x(_x), y(_y){}
};

struct Rect
{
  GLdouble l;
  GLdouble r;
  GLdouble d;
  GLdouble u;
  GLdouble width;
  GLdouble height;
  Rect(Point p1, Point p2)
  {
    if(p1.x < p2.x)
      {
	l = p1.x;
	r = p2.x;
      }
    else
      {
	l = p2.x;
	r = p1.x;
      }

    if(p1.y < p2.y)
      {
	d = p1.y;
	u = p2.y;
      }
    else
      {
	d = p2.y;
	u = p1.y;
      }

    width = r - l;
    height = u - d;
  }
};

#endif
