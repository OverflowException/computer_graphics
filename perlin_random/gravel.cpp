#include <GL/glut.h>
#include "perlin.cpp"
#include <algorithm>

int width = 800;
int height = 800;

//A decimal LUT to reduce floating point operations
vector<float> dec_lut;

void initDisplay();
void display();
void genDecLUT(float n, vector<float>& lut);

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(200, 200);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow("Unamed");

  genDecLUT(width / gw, dec_lut);
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


void display()
{
  glBegin(GL_POINTS);
  
  genGrad2D();
  
  int gridx, gridy, x, y;
  float avg;
  GLubyte color;

  for(gridx = 0; gridx < gw; ++gridx)
    for(gridy = 0; gridy < gh; ++gridy)
      for(x = 0; x < dec_lut.size(); ++x)
	for(y = 0; y < dec_lut.size(); ++y)
	  {
	    avg = perlin(gridx + dec_lut[x], gridy + dec_lut[y]);	    
	    color = (0.5 + avg) / 1 * 256;
	    glColor3ub(color, color, color);
	    glVertex2d(gridx + dec_lut[x], gridy + dec_lut[y]);
	  }
  
  glEnd();
  
  glFlush();
}

void genDecLUT(float n, vector<float>& lut)
{
  lut.resize(n);
  float value = 0;
  float offset = 1 / n;

  for_each(lut.begin(), lut.end(), [&](float& a)
	   {
	     a = value;
	     value += offset;
	   });
}
