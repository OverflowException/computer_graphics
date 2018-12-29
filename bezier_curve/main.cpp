#include <iostream>
#include <GL/glut.h>
#include "bezier.cpp"

int width = 640;
int height = 480;

void initDisplay();
void display();
void markCross(Point c);
void markSquare(Point c);

using namespace std;

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(200, 200);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow("Bezier");

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
  ControlPoints ctps;
  ctps.data[0] = {50, 240};
  ctps.data[1] = {200, 450};
  ctps.data[2] = {400, 50};
  ctps.data[3] = {600, 260};
  CurvePoints cvps = genBezier(ctps, 24);
  
  glColor3f(1, 1, 1);
  glBegin(GL_LINE_STRIP);
  for(int idx = 0; idx < cvps.num; ++idx)
    {
      glVertex2f(cvps.data[idx].x, cvps.data[idx].y);
    }
  glEnd();

  //Draw control points
  for(int idx = 0; idx < 4; ++idx)
    {
      markSquare(ctps.data[idx]);
    }

  //Draw curve points
  for(int idx = 0; idx < cvps.num; ++idx)
    {
      markCross(cvps.data[idx]);
    }
  
  glFlush();
}

void markCross(Point c)
{
  glColor3f(1, 0, 0);
  glBegin(GL_LINES);
  
  glVertex2f(c.x - 5, c.y + 5);
  glVertex2f(c.x + 5, c.y - 5);
  glVertex2f(c.x + 5, c.y + 5);
  glVertex2f(c.x - 5, c.y - 5);
  
  glEnd();  
}

void markSquare(Point c)
{
  glColor3f(0, 1, 0);
  glBegin(GL_LINE_LOOP);
  
  glVertex2f(c.x - 5, c.y + 5);
  glVertex2f(c.x + 5, c.y + 5);
  glVertex2f(c.x + 5, c.y - 5);
  glVertex2f(c.x - 5, c.y - 5);
  
  glEnd();  
}
