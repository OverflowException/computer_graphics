#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <GL/glut.h>
#include <cmath>
#include "image_utility.h"
#include "primitives.h"


const int width = 640;
const int height = 480;

Point p1(0, 0);
Point p2(200, 0);
Point mid = segPoint(p1, p2, 0.5);;
Point p3(mid.x, round(distance(p1, mid) * sqrt(3)));
Point center(mid.x, p3.y / 3);

void init()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0, width, 0.0, height);
}

void display()
{
  glColor3f(1, 1, 1);
  
  drawLine(p1, p2);
  drawLine(p2, p3);
  drawLine(p3, p1);
  drawLine(p3, mid);
  drawCircle(center, center.y);
  
  glFlush();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);  
  glutInitWindowSize(width, height);
  glutInitWindowPosition(100, 100);
  glutInitDisplayMode(GLUT_RGB);  
  glutCreateWindow("Graphic primitives");

  init();
  glutDisplayFunc(display);
  glutMainLoop();
    
  return 0;
}

