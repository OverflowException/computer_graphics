#ifndef _DISPLAY_UTILITY_H
#define _DISPLAY_UTILITY_H

#include <GL/glut.h>
#include "point_utility.h"
#include <cmath>

inline void setPixel(Pointi p)
{
  glVertex2i(p.x, p.y);
}

inline void setQuartPixel(Pointi p, Pointi center)
{
  glVertex2i(p.x + center.x, p.y + center.y);
  glVertex2i(p.x + center.x, -p.y + center.y);
  glVertex2i(-p.x + center.x, -p.y + center.y);
  glVertex2i(-p.x + center.x, p.y + center.y);
}

inline void setOctPixel(Pointi p, Pointi center)
{
  setQuartPixel(p, center);
  setQuartPixel(Pointi(p.y, p.x), center);
}

#endif
