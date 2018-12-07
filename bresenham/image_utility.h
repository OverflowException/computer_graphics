#ifndef _IMAGE_UTILITY_H
#define _IMAGE_UTILITY_H

#include <vector>
#include <GL/glut.h>

struct Point
{
  int x;
  int y;
Point(int x = 0, int y = 0) : x(x), y(y){};
};

inline void setPixel(Point p)
{
  glVertex2i(p.x, p.y);
}
  
inline void setQuartPixel(Point p, Point center)
{
  glVertex2i(p.x + center.x, p.y + center.y);
  glVertex2i(p.x + center.x, -p.y + center.y);
  glVertex2i(-p.x + center.x, -p.y + center.y);
  glVertex2i(-p.x + center.x, p.y + center.y);
}

inline void setOctPixel(Point p, Point center)
{
  setQuartPixel(p, center);
  setQuartPixel(Point(p.y, p.x), center);
}

Point segPoint(Point p1, Point p2, float m);
float distance(Point p1, Point p2);

#endif
