#include <GL/glut.h>
#include <unistd.h>
#include <iostream>

int width = 640;
int height = 480;

//This is an arrow pointing up
GLubyte bitShape[20] =
  {
    0x1c, 0x00, 0x1c, 0x00, 0x1c, 0x00, 0x1c, 0x00, 0x1c, 0x00,
    0xff, 0x80, 0x7f, 0x00, 0x3e, 0x00, 0x1c, 0x00, 0x08, 0x00
  };


void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  /*1st and 2nd para is width, height of bitmap,
  3rd and 4th para indicates which position in the bitmap will be regarded as origin, 
  relative to model(bitmap) coordinate
  which will be placed at raster's origin point
  5th and 6th para indicates offset of raster after one display callback*/
  glBitmap(9, 10, 0, 0, 20.0, 15.0, bitShape);
  
  glFlush();
}

void keyPressed(unsigned char key, int x, int y)
{
  std::cout << "Pressed key " << key;
  std::cout << " Mouse at (" << x << ", " << y << ")" << std::endl;

  if(key == 'q')
    {
      std::cout << "Exit" << std::endl;
      exit(0);
    }

  //Post a redisplay message to message queue
  glutPostRedisplay();
}

void initDisplay()
{
  glClearColor(0.3, 0.3, 0.3, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);

  //This matrix is applied to project actual coordinates to screen coordinates
  gluOrtho2D(0.0, width, 0.0, height);
  glColor3f(0, 1, 0);
  
  //Indicates how a bitmap is stored
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  //Indicates where the origin point of raster is placed, relative to world coordinate
  glRasterPos2i(0, 0);
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);  
  glutInitWindowSize(width, height);
  glutInitWindowPosition(200, 200);
  glutInitDisplayMode(GLUT_RGB);  
  glutCreateWindow("OpenGL Test");

  initDisplay();
  glutKeyboardFunc(keyPressed);
  glutDisplayFunc(display);
  glutMainLoop();
  
  return 0;
}
