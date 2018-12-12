#include <GL/glut.h>
#include <unistd.h>
#include <iostream>
#include <cmath>

int width = 640;
int height = 480;
int radius = 100;
int centerx = width / 2;
int centery = height / 2;

inline float dist(int x1, int y1, int x2, int y2)
{
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void display()
{
  glColor3f(1, 1, 1);
  glBegin(GL_POINTS);

  float illumi = 0.0;
  float distance;
  for(int x = 0; x < width; ++x)
    for(int y = 0; y < height; ++y)
      if((distance = dist(centerx, centery, x, y)) < radius)
	{
	  glColor3f(1, 1, 1);
  	  glVertex2i(x, y);
	}
      else
	{
	  //Ray tracing
	  illumi = asin(radius / distance) / M_PI;
	  glColor3f(illumi, illumi, illumi);
	  glVertex2i(x, y);
	}

  glEnd();
  glFlush();
}

void keyPressed(unsigned char key, int x, int y)
{
  switch(key)
    {
    case 'w':
      centery += 10;
      break;
    case 'a':
      centerx -= 10;
      break;
    case 's':
      centery -= 10;
      break;
    case 'd':
      centerx += 10;
      break;
    }  
  
  glutPostRedisplay();
}

void initDisplay()
{
  glClearColor(0.3, 0.3, 0.3, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);

  gluOrtho2D(0.0, width, 0.0, height);
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(200, 200);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow("Ray Tracing");

  initDisplay();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyPressed);
  glutMainLoop();
}
