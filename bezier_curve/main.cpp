#include <iostream>
#include <GL/glut.h>
#include "bezier.cpp"

int width = 640;
int height = 480;

int currCtIdx = 0;
ControlPoints ctps;

void initDisplay();
void initControlPoints();
void display();
void keyPressed(unsigned char key, int x, int y);
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

  initControlPoints();
  initDisplay();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyPressed);
  glutMainLoop();

  return 0;
}

void initControlPoints()
{
  ctps.data[0] = {50, 240};
  ctps.data[1] = {200, 450};
  ctps.data[2] = {400, 50};
  ctps.data[3] = {600, 260};
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
  CurvePoints cvps = genBezier(ctps, 24);

  //Draw the curve as line segments
  glClear(GL_COLOR_BUFFER_BIT);
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

void keyPressed(unsigned char key, int x, int y)
{
  std::cout << "Pressed key " << key;
  std::cout << " Mouse at (" << x << ", " << y << ")" << std::endl;

  switch(key)
    {
    case 'q':
      std::cout << "Exit" << std::endl;
      exit(0);
      break;
      
    case '0':
      currCtIdx = 0;
      break;
      
    case '1':
      currCtIdx = 1;
      break;
      
    case '2':
      currCtIdx = 2;
      break;
      
    case '3':
      currCtIdx = 3;
      break;

    case 'a':
      ctps.data[currCtIdx].x -= 5;
      break;
    case 'w':
      ctps.data[currCtIdx].y += 5;
      break;
    case 's':
      ctps.data[currCtIdx].y -= 5;
      break;
    case 'd':
      ctps.data[currCtIdx].x += 5;
      break;
    }
  
  //Post a redisplay message to message queue
  glutPostRedisplay();
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
