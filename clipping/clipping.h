#ifndef _CLIPPING_H
#define _CLIPPING_H

#include "geo.h"

const GLubyte upbit = 0x8;
const GLubyte downbit = 0x4;
const GLubyte rightbit = 0x2;
const GLubyte leftbit = 0x1;

//Generate region code for Cohen-Sutherland line clipping algo
inline GLubyte encode(Point p, const Rect& rect)
{
  
  GLubyte result = 0;
  if(p.y > rect.u)
    result |= upbit;
  if(p.y < rect.d)
    result |= downbit;
  if(p.x > rect.r)
    result |= rightbit;
  if(p.x < rect.l)
    result |= leftbit;

  return result;
}
bool lineClipCoSu(Point&, Point&, const Rect&);
void lineClipCoSu_aux(Point&, GLubyte, GLdouble, GLdouble, const Rect&);

bool lineClipLiBa(Point&, Point&, const Rect&);
bool lineClipLiBa_aux(GLdouble, GLdouble, GLdouble&, GLdouble&);

#endif
