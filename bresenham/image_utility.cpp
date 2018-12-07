#include "image_utility.h"
#include <iostream>
#include <GL/glut.h>
#include <cmath>


Point segPoint(Point p1, Point p2, float m)
{
  float n = 1 - m;
  return Point(n * p1.x + m * p2.x, n * p1.y + m * p2.y);
}

float distance(Point p1, Point p2)
{
  return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
