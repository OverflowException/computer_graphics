#include <GL/glut.h>
#include "perlin.cpp"


int width = 1280;
int height = 1280;


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


void display()
{
  glBegin(GL_POINTS);
  
  genGrad2D();
  
  int x, y;
  double offsetx, offsety, prod0, prod1, prod2, prod3, avg;
  GLubyte color;
  
  for(int x = 0; x < gw - 2; ++x)
    for(int y = 0; y < gh - 2; ++y)
      for(double offsetx = 0; offsetx < 1; offsetx += 0.1)
	for(double offsety = 0; offsety < 1; offsety += 0.1)
	    {
	      avg = perlin(x + offsetx, y + offsety);
	      //cout << "Here " << x + offsetx << " " << y + offsety << endl;
	      // //Generate 4 dot products	    
	      // prod0 = dot(x, y, offsetx, offsety);
	      // prod1 = dot(x + 1, y, offsetx, offsety);
	      // prod2 = dot(x, y + 1, offsetx, offsety);
	      // prod3 = dot(x + 1, y + 1, offsetx, offsety);

	      // avg = lerp(lerp(prod0, prod1, offsetx), lerp(prod2, prod3, offsetx), offsety);
	      //cout << avg << endl;
	      //glColor3d(avg + 0.5, avg + 0.5, avg + 0.5);
	      color = (1 + avg) / 2 * 256;
	      glColor3ub(color, color, color);
	      glVertex2d(x + offsetx, y + offsety);
	    }

  
  glEnd();
  
  glFlush();
}
