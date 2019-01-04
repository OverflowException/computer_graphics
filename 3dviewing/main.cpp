#include <iostream>
#include <unistd.h>
#include <GL/glut.h>
#include "ortho.h"
#include "../transforms/transforms.h"
#include "../utilities/entity_utility.h"

using namespace std;

int width = 640;
int height = 480;
bool mouseDown = false;

Entity<double> ent;
Entity<double> entScreen;

struct Camera
{
  Pointd pos;
  Vec3d orient;
  Vec3d horizon;
  Vec3d vertical;
  double pfactor;
};

struct MouseAction
{
  int btn;
  bool down;
  int x;
  int y;
};

Camera cam =
  {
    {0, 0, 200},
    {0, 0, -1},
    {1, 0, 0},
    {0, 1, 0},
    1.0
  };

MouseAction mAct =
  {
    -1, false, 0, 0
  };

void initEntity();
void initDisplay();
Camera orbitCamera(Camera cam, double depthc, double vangle, double hangle);
void transformEntity();
void drawEntity();
void display();
void mouseHandler(int button, int state, int x, int y);
void motionHandler(int x, int y);

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
  glutMouseFunc(mouseHandler);
  glutMotionFunc(motionHandler);
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

  ent.addVert({-100, -100, 50});
  ent.addVert({100, -100, 50});
  ent.addVert({100, 100, 50});
  ent.addVert({-100, 100, 50});

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

//This function is pretty fucked up
Camera orbitCamera(Camera cam, double depthc, double vangle, double hangle)
{
  Pointd center = add(cam.pos, mul(cam.orient, depthc));
  TransMat3d vTransMat, hTransMat, mat;
  rotate3d(vTransMat, center, sub(center, cam.horizon), vangle);
  rotate3d(hTransMat, center, add(center, cam.vertical), hangle);

  compositeTrans3d(vTransMat, hTransMat, hTransMat);
  cleanError4x4(hTransMat, 10E-6);

  Camera rcam;
  rcam.pos = transform3d(hTransMat, cam.pos);
  rcam.orient = transform3d(hTransMat, cam.orient);
  rcam.horizon = transform3d(hTransMat, cam.horizon);
  rcam.vertical = transform3d(hTransMat, cam.vertical);
  rcam.pfactor = cam.pfactor;
  return rcam;
}


void transformEntity()
{
  for(int idx = 0; idx < ent.verts.size(); ++idx)
    ent.verts[idx] = transform3d(tMat, ent.verts[idx]);
}

void drawEntity()
{
  entScreen = ent;

  //Update view matrix
  ortho3d(vMat, cam.pos, cam.orient, cam.horizon);

  //Calculate entity on sreen
  for(int idx = 0; idx < ent.verts.size(); ++idx)
    entScreen.verts[idx] = view(vMat, ent.verts[idx], cam.pfactor, width, height);

  //Draw entity on screen
  glBegin(GL_LINES);
  for(const typename decltype(entScreen)::edge_type& e : entScreen.edges)
    {
      //Check depth. Any edge with negative depth vertex will not be drawn
      if(entScreen.verts[e.start].z >=0 && entScreen.verts[e.end].z >=0)
	{
	  glColor3fv((GLfloat*)&e.color);
	  glVertex2d(entScreen.verts[e.start].x, entScreen.verts[e.start].y);
	  glVertex2d(entScreen.verts[e.end].x, entScreen.verts[e.end].y);
	}
    }
  glEnd();
  glFlush();
}

void display()
{
  //No depth detection involved
  //Depth detection can be implemented by checking Z coodinate of screen coordinates. Negative value is 'behind' camera

  glClear(GL_COLOR_BUFFER_BIT);
  transformEntity();
  drawEntity();
}


void mouseHandler(int button, int state, int x, int y)
{
  //Mouse y coordinate is opposite to OpenGL coordinate
  y = height - y;
  std::cout << "mouse btn = " << button << ", state = " << state << ", x = " << x << ", y = " << y << std::endl;

  //Some button pressed
  if(state == 0)
    {
      mAct.btn = button;
      mAct.down = true;
      mAct.x = x; mAct.y = y;
    }

  //Some button released
  else
    {
      mAct.btn = -1;
      mAct.down = state;
    }
}

//This will only be called when some button is pressed
//Will not be called when free moving
void motionHandler(int x, int y)
{
  y = height - y;
  std::cout << "motion x = " << x << ", y = " << y << std::endl;

  TransMat3d tmpMat;
  int dx = x - mAct.x, dy = y - mAct.y;
  //Left button down
  if(mAct.btn == 0)
    {
      rotate3d(tmpMat, {0, 0, 0}, cam.vertical, dx); //horizontal rotation
      rotate3d(tMat, {0, 0, 0}, sub({0, 0, 0}, cam.horizon), dy); //vertical rotation
      compositeTrans3d(tmpMat, tMat, tMat);

    }

  //Right button down
  else if(mAct.btn == 2)
    {
      translate3d(tMat, dx, dy, 0);
    }


  //Update mouse position
  mAct.x = x;
  mAct.y = y;
  glutPostRedisplay();
}
