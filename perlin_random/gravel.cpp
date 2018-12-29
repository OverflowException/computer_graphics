#include <GL/glut.h>
#include "perlin.cpp"


int width = 768;
int height = 768;


void initDisplay();
void display();



int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(200, 200);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow("Unamed");

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

  gluOrtho2D(0.0, (GLdouble)gw, 0.0, (GLdouble)gh);
}

array<float, 10> dec_map = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};

void display()
{
  glBegin(GL_POINTS);
  
  genGrad2D();
  
  int gridx, gridy, x, y;
  float avg;
  GLubyte color;

  for(gridx = 0; gridx < gw - 1; ++gridx)
    for(gridy = 0; gridy < gh - 1; ++gridy)
      for(x = 0; x < 10; ++x)
	for(y = 0; y < 10; ++y)
	  {
	    avg = perlin(gridx + dec_map[x], gridy + dec_map[y]);	    
	    color = (0.5 + avg) / 1 * 256;
	    glColor3ub(color, color, color);
	    glVertex2d(gridx + dec_map[x], gridy + dec_map[y]);
	  }
  
  glEnd();
  
  glFlush();
}
