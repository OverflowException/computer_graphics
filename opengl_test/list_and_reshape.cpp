/*
  This is so fucking confusing. 
  How does reshape callback function work?
  How does register list work?
 */

#include <GL/glut.h>
#include <iostream>
#include <cmath>

int width = 400;
int height = 400;
int hexcx = width / 2;
int hexcy = height / 2;
unsigned int regHex = 0;
double theta;

int testInt = 0;

void initDisplay()
{
  glClearColor(0.3, 0.3, 0.3, 0.0);
  glMatrixMode(GL_PROJECTION);
  
  regHex = glGenLists(1);
  theta = 2 * M_PI / 6;
  double angle = 0;
  double x, y;
  
  /*So it look like this compiled list can only register OpenGL commands,
    and variables inside 
   */
  glNewList(regHex, GL_COMPILE);

  std::cout << "reg list" << std::endl;
  glColor3f(1, 0, 0);
  glBegin(GL_POLYGON);
  
  for(int idx = 0; idx < 6; ++idx)
    {
      ++testInt;
      angle += theta;
      x = hexcx + 150 * cos(angle);
      y = hexcy + 150 * sin(angle);
      glVertex2d(x, y);
    }  
  glEnd();

  glEndList();
}

void regHexagon()
{
  //glMatrixMode(GL_PROJECTION);
  //glLoadIdentity();
  gluOrtho2D(0.0, (GLdouble)width, 0.0, (GLdouble)height);
  //glClear(GL_COLOR_BUFFER_BIT);
  
  glCallList(regHex);
  glFlush();
}

void reshape(int newWidth, int newHeight)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  width = newHeight;
  height = newHeight;
  //Ortho here does not seem to work
  //gluOrtho2D(0.0, (GLdouble)newWidth, 0.0, (GLdouble)newHeight);  
  
  glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(200, 200);
  glutInitDisplayMode(GLUT_RGB);
  glutCreateWindow("OpenGL Test");

  initDisplay();
  glutDisplayFunc(regHexagon);
  //glutReshapeFunc(reshape);
  glutMainLoop();
}

