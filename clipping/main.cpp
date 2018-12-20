#include "geo.h"
#include "clipping.h"
#include <ctime>

int width = 640;
int height = 480;

int cxmin = 270;
int cxmax = 370;
int cymin = 190;
int cymax = 290;

void initDisplay();
void display();
void display_aux();

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(200, 200);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow("Liang-Barsk line clipping");
  
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
      //if(lineClipCoSu(p1, p2, border))
      if(lineClipLiBa(p1, p2, border))
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

  //lineClipCoSu(p1, p2, border);
  lineClipLiBa(p1, p2, border);  
  glBegin(GL_LINES);
  glColor3f(1, 0, 0);
  glVertex2d(p1.x, p1.y);
  glVertex2d(p2.x, p2.y);
  glEnd();
  
  glFlush();
}
