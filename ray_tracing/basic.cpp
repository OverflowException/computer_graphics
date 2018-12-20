#include <GL/glut.h>
#include <unistd.h>
#include <iostream>
#include <cmath>
#include <random>

int width = 640;
int height = 480;
int radius = 50;
int centerx = width / 2;
int centery = height / 2;

#define TWO_PI 6.28318530718f
#define N 64
#define MAX_STEP 10
#define MAX_DISTANCE 500
#define EPSILON 1e-6f

//Calculate Singned Distance Field of a circle
inline float circleSDF(float x, float y, float cx, float cy, float r)
{
  return sqrt(pow(cx - x, 2) + pow(cy - y, 2)) - r;
}

//Ray marching method of ray tracing
float trace(float ox, float oy, float dx, float dy)
{
  float t;
  for(int i = 0; i < MAX_STEP && t < MAX_DISTANCE; ++i)
    {
      float sd = circleSDF(ox + dx * t, oy + dy * t, centerx, centery, radius);
      if(sd < EPSILON)
	return 2.0;
      t += sd;
    }

  return 0;
}

//Direction sampling
float sample(float x, float y)
{
  float sum = 0;
  for(int i = 0; i < N; ++i)
    {
      //Jittered sampling
      float a = TWO_PI * (i + (float)std::rand() / RAND_MAX) / N;
      sum += trace(x, y, cos(a), sin(a));
    }
  return sum / N;
}

void display()
{
  glBegin(GL_POINTS);
  int x, y;
  float illumi;
  for(x = 0; x < width; ++x)
    for(y = 0; y < height; ++y)
      {
	illumi = sample(x, y);
	glColor3f(illumi, illumi, illumi);
	glVertex2i(x, y);
      }
  glEnd();
  
  glFlush();
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
  glutMainLoop();
}
