#include <iostream>
#include <GL/glut.h>
#include "ortho.cpp"

using namespace std;

int width = 640;
int height = 480;

void initDisplay();
void initTetra();
void display();

ViewMat3d vMat;
Point3d tetra[4];

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(200, 200);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow("Unamed");

  initTetra();
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

  //gluOrtho2D(0.0, (GLdouble)width, 0.0, (GLdouble)height);
  gluOrtho2D(-(GLdouble)width / 2, (GLdouble)width / 2, -(GLdouble)height / 2, (GLdouble)height / 2);
  //Init view matrix
  ortho3d(vMat,
	  {0, 100, 100},
	  {0, -1, -1},
	  {1, 0, 0});
}

void initTetra()
{
  tetra[0] = {-100.0, -100.0/sqrt(3), 0};
  tetra[1] = {100.0, -100.0/sqrt(3), 0};
  tetra[2] = {0, 200.0/sqrt(3), 0};
  tetra[3] = {0, 0, 500.0 * sqrt(2) / 3.0};
}

void display()
{
  Point3d screenTetra[4];
  for(int idx = 0; idx < 4; ++idx)
    {
      screenTetra[idx] = view(vMat, tetra[idx]);
      cout << "(" << screenTetra[idx].x << ", " << screenTetra[idx].y << ", " << screenTetra[idx].z << ")" << endl;
    }  

  //No depth detection involved
  //Depth detection can be implemented by checking Z coodinate of screen coordinates. Negative value is 'behind' camera
  glColor3f(1, 1, 1);
  for(int idx1 = 0; idx1 < 4; ++idx1)
    for(int idx2 = idx1 + 1; idx2 < 4; ++idx2)
      {
	glBegin(GL_LINES);
	glVertex2d(screenTetra[idx1].x, screenTetra[idx1].y);
	glVertex2d(screenTetra[idx2].x, screenTetra[idx2].y);
	glEnd();
      }
  
  glFlush();
}
