#include "geo.h"
#include "clipping.h"

//This function can only return false when direct reject happens.
//Cannot return false at all rejects
bool lineClipCoSu(Point& p1, Point& p2, const Rect& rect)
{
  GLubyte code1 = encode(p1, rect);
  GLubyte code2 = encode(p2, rect);

  //Accept
  if(!(code1 | code2))
    return true;
  //Reject
  else if(code1 & code2)
    return false;

  //Clip
  GLdouble dx = p1.x - p2.x;
  GLdouble dy = p1.y - p2.y;
  lineClipCoSu_aux(p1, code1, dx, dy, rect);
  lineClipCoSu_aux(p2, code2, dx, dy, rect);
  return true;
}

void lineClipCoSu_aux(Point& p, GLubyte code, GLdouble dx, GLdouble dy, const Rect& rect)
{
  GLdouble slope = 0.0;
  //Lined up vertically, infini slope
  if(dx == 0.0)
    {
      if(p.y > rect.u)
	p.y = rect.u;
      else if(p.y < rect.d)
	p.y = rect.d;
    }

  //Lined up horizontally, 0 slope
  else if(dy == 0.0)
    {
      if(p.x > rect.r)
	p.x = rect.r;
      else if(p.x < rect.l)
	p.x = rect.l;
    }

  //Not lined up in neither direction
  else
    {
      slope = dy / dx;
      //Above upper bound
      if(p.y > rect.u)
	{
	  p.x += (rect.u - p.y) / slope;
	  p.y = rect.u;
	}
      //Below lower bound
      else if(p.y < rect.d)
	{
	  p.x += (rect.d - p.y) / slope;
	  p.y = rect.d;
	}

      //Left of left bound
      if(p.x < rect.l)
	{
	  p.y += (rect.l - p.x) * slope;
	  p.x = rect.l;
	}
      //Right of right bound
      else if(p.x > rect.r)
	{
	  p.y += (rect.r - p.x) * slope;
	  p.x = rect.r;
	}
    }
}

bool lineClipLiBa(Point& p1, Point& p2, const Rect& rect)
{  
  GLdouble dx = p2.x - p1.x;
  GLdouble dy = p2.y - p1.y;
  
  GLdouble u1 = 0.0, u2 = 1.0;

  if(lineClipLiBa_aux(-dx, p1.x - rect.l, u1, u2) &&
     lineClipLiBa_aux(dx, rect.r - p1.x, u1, u2) &&
     lineClipLiBa_aux(-dy, p1.y - rect.d, u1, u2) &&
     lineClipLiBa_aux(dy, rect.u - p1.y, u1, u2))
    {
      //Update p2 first. Because p2 is calculated based on original value of p1.
      if(u2 != 1.0)
	p2 = Point(p1.x + u2 * dx, p1.y + u2 * dy);
      if(u1 != 0.0)
	p1 = Point(p1.x + u1 * dx, p1.y + u1 * dy);
      return true;
    }

  return false;
}

//Updates u1 or u2, check validity at the same time
bool lineClipLiBa_aux(GLdouble p, GLdouble q, GLdouble& u1, GLdouble& u2)
{
  GLdouble r = 0;

  //Prallel to clipping edge
  if(p == 0)
    if(q < 0)
      return false;
    else
      return true;

  r = q / p;
  //Update u1
  if(p < 0)
    {
      if(r > u1)
	u1 = r;
    }
  //Update u2
  else if(p > 0)
    {
      if(r < u2)
	u2 = r;
    }

  if(u1 >= u2)
    return false;
  else
    return true;
}
