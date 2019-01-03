#ifndef _ARITHMETICS_H
#define _ARITHMETICS_H

#include "../utilities/point_utility.h"

template<typename Point>
Point segPoint(Point p1, Point p2, double m)
{
  double n = 1 - m;
  return Point(n * p1.x + m * p2.x, n * p1.y + m * p2.y);
}

template<typename Point>
double distance(Point p1, Point p2)
{
  return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

#endif
