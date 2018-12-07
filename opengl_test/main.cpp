#include <GL/glut.h>

int width = 640;
int height = 480;

void display()
{
  glColor3f(1, 1, 1);

  glBegin(GL_LINE_STRIP);

  glVertex2i(0, 0);
  glVertex2i(5, 50);
  glVertex2i(200, 0);
  glVertex2i(300, 50);
  
  glEnd();

  glFlush();
}

void init()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);

  glMatrixMode(GL_PROJECTION);

  //This matrix is applied to project actual coordinates to screen coordinates
  gluOrtho2D(0.0, width, 0.0, height);
}


int main(int argc, char** argv)
{
  glutInit(&argc, argv);  
  glutInitWindowSize(width, height);
  glutInitWindowPosition(200, 200);
  glutInitDisplayMode(GLUT_RGB);  
  glutCreateWindow("OpenGL Test");

  init();
  glutDisplayFunc(display);
  glutMainLoop();
  
  return 0;
}
