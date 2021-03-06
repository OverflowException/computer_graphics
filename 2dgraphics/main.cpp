#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <GL/glut.h>
#include <cmath>
#include "display_utility.h"
#include "primitives.h"
#include "../transforms/transforms.h"
#include "arithmetics.h"
#include "../utilities/entity_utility.h"

const int width = 640;
const int height = 480;

Entity<double> emulet;

template<typename Entity>
void drawEntity(const Entity& ent)
{ 
  for(const typename Entity::edge_type& e : ent.edges)
    {
      glColor3fv((GLfloat*)&e.color);
      drawLine(ent.verts[e.start], ent.verts[e.end]);
    }
}

//This transform function cannot deal with scaling of circle
void transformEntity2d(TransMat2d mat, Entity<double>& ent)
{
  double x, y;
  for(Pointd& p : ent.verts)
    {
      x = p.x;
      y = p.y;
      p.x = mat[0][0] * x + mat[0][1] * y + mat[0][2];
      p.y = mat[1][0] * x + mat[1][1] * y + mat[1][2];
    }
}

//Constructs something like the Deathly Hallows in Harry Potter
void construct(Entity<double>& ent)
{  
  Pointd p1(0, 0);
  Pointd p2(200, 0);
  Pointd mid = segPoint(p1, p2, 0.5);;
  Pointd p3(mid.x, distance(p1, mid) * sqrt(3));
  Pointd center(mid.x, p3.y / 3);

  ent.addVert(p1);
  ent.addVert(mid);
  ent.addVert(p2);
  ent.addVert(p3);
  ent.addVert(center);

  decltype(emulet)::color_type yellow = {1, 1, 0};
  
  ent.addEdge(0, 2, yellow);
  ent.addEdge(0, 3, yellow);
  ent.addEdge(1, 3, yellow);
  ent.addEdge(2, 3, yellow);
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

