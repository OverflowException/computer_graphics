#include <GL/glut.h>
#include <random>
#include <vector>
#include <iostream>

int width = 640;
int height = 480;

int cxmin = 100;
int cxmax = 600;
int cymin = 100;
int cymax = 400;

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


void initDisplay();
void display();
void display_aux();
bool lineClipCoSu(Point&, Point&, const Rect&);
void lineClipCoSu_aux(Point&, GLubyte, GLdouble, GLdouble, const Rect&);

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(200, 200);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow("Unamed");

  initDisplay();
  glutDisplayFunc(display);
  //glutKeyboardFunc(/*Callback*/);
  glutMainLoop();

  return 0;
}
  
void initDisplay()
{
  glClearColor(0.3, 0.3, 0.3, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);

  gluOrtho2D(0.0, (GLdouble)width, 0.0, (GLdouble)height);
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  
  Rect border(Point(cxmin, cymin), Point(cxmax, cymax));
  
  //Draw clipping borders
  glBegin(GL_LINE_LOOP);
  glColor3f(1.0, 1.0, 1.0);
  glVertex2d(border.l, border.d);
  glVertex2d(border.r, border.d);
  glVertex2d(border.r, border.u);
  glVertex2d(border.l, border.u);
  glEnd();
  
  glBegin(GL_LINES);
  Point p1, p2;
  std::srand((unsigned)time(NULL));
  for(int idx = 0; idx < 16; ++idx)
    {
      p1.x = std::rand() % width;
      p1.y = std::rand() % height;
      
      p2.x = std::rand() % width;
      p2.y = std::rand() % height;

      //Draw this line without clipping
      glColor3f(0, 1, 0);
      glVertex2d(p1.x, p1.y);
      glVertex2d(p2.x, p2.y);

      //Get a clipped version of this line
      //If there is still some segment left in clipping boundary
      if(lineClipCoSu(p1, p2, border))
	{
	  glColor3f(1, 0, 0);
	  glVertex2d(p1.x, p1.y);
	  glVertex2d(p2.x, p2.y);
	}
    }  
  glEnd();
  
  glFlush();
}

void display_aux()
{
  glClear(GL_COLOR_BUFFER_BIT);

  Rect border(Point(cxmin, cymin), Point(cxmax, cymax));
  
  //Draw clipping borders
  glBegin(GL_LINE_LOOP);
  glColor3f(1.0, 1.0, 1.0);
  glVertex2d(border.l, border.d);
  glVertex2d(border.r, border.d);
  glVertex2d(border.r, border.u);
  glVertex2d(border.l, border.u);
  glEnd();

  Point p1(border.r + 5, border.u + 10);
  Point p2(border.l + 52, border.u - 134);

  glBegin(GL_LINES);
  glColor3f(0, 1, 0);
  glVertex2d(p1.x, p1.y);
  glVertex2d(p2.x, p2.y);
  glEnd();

  lineClipCoSu(p1, p2, border);  
  glBegin(GL_LINES);
  glColor3f(1, 0, 0);
  glVertex2d(p1.x, p1.y);
  glVertex2d(p2.x, p2.y);
  glEnd();

  
  glFlush();
}

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
  printf("(%f, %f), (%f, %f) -> ", p1.x, p1.y, p2.x, p2.y);
  GLdouble dx = p1.x - p2.x;
  GLdouble dy = p1.y - p2.y;
  lineClipCoSu_aux(p1, code1, dx, dy, rect);
  lineClipCoSu_aux(p2, code2, dx, dy, rect);
  printf("(%f, %f), (%f, %f)\n", p1.x, p1.y, p2.x, p2.y);
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
