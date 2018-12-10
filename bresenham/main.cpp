#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <GL/glut.h>
#include <cmath>
#include "image_utility.h"
#include "primitives.h"
#include "transforms.h"


const int width = 640;
const int height = 480;

Entity emulet;

//Constructs something like the Deathly Hallows in Harry Potter
void construct(Entity& ent)
{  
  Point p1(0, 0);
  Point p2(200, 0);
  Point mid = segPoint(p1, p2, 0.5);;
  Point p3(mid.x, round(distance(p1, mid) * sqrt(3)));
  Point center(mid.x, p3.y / 3);

  ent.addVert(p1);
  ent.addVert(mid);
  ent.addVert(p2);
  ent.addVert(p3);
  ent.addVert(center);

  ent.addEdge(0, 2);
  ent.addEdge(0, 3);
  ent.addEdge(1, 3);
  ent.addEdge(2, 3);
  ent.addCircle(4, center.y);

  ent.setColor(1, 1, 0);
}

void init()
{
  glClearColor(0.2, 0.2, 0.2, 0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0, width, 0.0, height);
}

void display()
{
  TransMat2d mtrans;
  translate2d(mtrans, width / 2 - emulet.verts[4].x, height / 2 - emulet.verts[4].y);
  transformEntity2d(mtrans, emulet);
  
  rotate2d(mtrans, emulet.verts[4], 10);
  while(true)
    {
      glClear(GL_COLOR_BUFFER_BIT);
      transformEntity2d(mtrans, emulet);
      drawEntity(emulet);
      glFlush();
      usleep(100000);
    }
}

int main(int argc, char** argv)
{  
  glutInit(&argc, argv);  
  glutInitWindowSize(width, height);
  glutInitWindowPosition(100, 100);
  glutInitDisplayMode(GLUT_RGB);  
  glutCreateWindow("Graphic primitives");

  construct(emulet);
  
  init();
  glutDisplayFunc(display);
  glutMainLoop();
    
  return 0;
}

