#include <iostream>
#include <unistd.h>
#include <GL/glut.h>
#include "ortho.h"
#include "../transforms/transforms.h"
#include "../utilities/entity_utility.h"

using namespace std;

struct Camera
{
  Pointd pos;
  Vec3d orient;
  Vec3d horizon;
  Vec3d vertical;
  double pfactor;
};

int width = 640;
int height = 480;

Entity<double> ent;
Entity<double> entScreen;

Camera cam = {{200, 0, 0},
	      {-1, 0, 0},
	      {0, 1, 0},
	      {0, 0, 1},
	      0.2
};

void initEntity();
void initDisplay();
void orbitCamera(Camera& camera, double depthc, double vangle, double hangle);
void displayEntity();
void display();

ViewMat3d vMat;
TransMat3d tMat;

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(200, 200);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow("Unamed");

  initEntity();
  initDisplay();
  glutDisplayFunc(display);
  //glutKeyboardFunc(/*Callback*/);
  glutMainLoop();

  return 0;
}

void initEntity()
{
  //Contruct a prism
  ent.addVert({-100, -100, -50});
  ent.addVert({100, -100, -50});
  ent.addVert({100, 100, -50});
  ent.addVert({-100, 100, -50});

  ent.addVert({-80, -80, 50});
  ent.addVert({80, -80, 50});
  ent.addVert({80, 80, 50});
  ent.addVert({-80, 80, 50});

  decltype(ent)::color_type nred = {0, 1, 1};
  decltype(ent)::color_type ngreen = {1, 0, 1};
  decltype(ent)::color_type nblue = {1, 1, 0};
  
  ent.addEdge(0, 1, nblue);
  ent.addEdge(1, 2, nblue);
  ent.addEdge(2, 3, nblue);
  ent.addEdge(3, 0, nblue);

  ent.addEdge(4, 5, nred);
  ent.addEdge(5, 6, nred);
  ent.addEdge(6, 7, nred);
  ent.addEdge(7, 4, nred);

  ent.addEdge(0, 4, ngreen);
  ent.addEdge(1, 5, ngreen);
  ent.addEdge(2, 6, ngreen);
  ent.addEdge(3, 7, ngreen);
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
	  cam.pos,
	  cam.orient,
	  cam.horizon);
  
  //Init transform matrix
  setIdentity3d(tMat);
}

void orbitCamera(Camera& cam, double depthc, double vangle, double hangle)
{
  Pointd center = add(cam.pos, mul(cam.orient, depthc));
  TransMat3d mat;
  if(vangle != 0)
    {
      rotate3d(mat, center, sub(center, cam.horizon), vangle);
      cam.pos = transform3d(mat, cam.pos);
      cam.orient = transform3d(mat, cam.orient);
      cam.vertical = transform3d(mat, cam.vertical);
    }
  if(hangle != 0)
    {
      rotate3d(mat, center, add(center, cam.vertical), hangle);
      cam.pos = transform3d(mat, cam.pos);
      cam.orient = transform3d(mat, cam.orient);
      cam.horizon = transform3d(mat, cam.horizon);
    }
}

void displayEntity()
{
  entScreen = ent;

  //Update view matrix
  ortho3d(vMat, cam.pos, cam.orient, cam.horizon);

  //Calculate entity on sreen
  for(int idx = 0; idx < ent.verts.size(); ++idx)
    entScreen.verts[idx] = view(vMat, transform3d(tMat, ent.verts[idx]), cam.pfactor, width, height);

  //Draw entity on screen
  glBegin(GL_LINES);
  for(const typename decltype(entScreen)::edge_type& e : entScreen.edges)
    { 
      glColor3fv((GLfloat*)&e.color);
      glVertex2d(entScreen.verts[e.start].x, entScreen.verts[e.start].y);
      glVertex2d(entScreen.verts[e.end].x, entScreen.verts[e.end].y);
    }
  glEnd();
  glFlush();
}

void display()
{
  //No depth detection involved
  //Depth detection can be implemented by checking Z coodinate of screen coordinates. Negative value is 'behind' camera
  glClear(GL_COLOR_BUFFER_BIT);
  displayEntity();      
}
