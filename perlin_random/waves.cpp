#include <GL/glut.h>
#include "perlin.cpp"
#include <algorithm>
#include <unistd.h>

const int width = 800;
const int height = 800;

const float wratio = width / gw;
const float hratio = height / gh;

const int waveMaxAmp = 50;
const int waveHorizon = 400;

const int waveSpan = width;
const int wavePeriod = height;

//A decimal LUT to reduce floating point operations
vector<float> dec_lut;

void initDisplay();
void display();
void genPattern();
void genDecLUT(float n, vector<float>& lut);

vector<vector<float>> pattern(wavePeriod, vector<float>(waveSpan, 0));

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(200, 200);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow("Unamed");

  //Generate wave patterns
  genDecLUT(wratio, dec_lut);
  genPattern();
  initDisplay();
  glutDisplayFunc(display);
  //glutKeyboardFunc(/*Callback*/);
  glutMainLoop();

  return 0;
}
  
void initDisplay()
{
  glClearColor(0.5, 0.5, 0.5, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);

  //Height of ortho doesnt really matter, just dont make vertical distortion too unacceptable
  gluOrtho2D(0.0, (GLdouble)waveSpan, 0.0, (GLdouble)height);
}

void genPattern()
{
  genGrad2D();
  
  int gridx, gridy, gridbasex, gridbasey, x, y;
  float avg;
  GLubyte color;

  for(gridx = 0; gridx < gw; ++gridx)
    for(gridy = 0; gridy < gh; ++gridy)
      {
	gridbasex = gridx * wratio;
	gridbasey = gridy * hratio;
	  for(x = 0; x < wratio; ++x)
	    for(y = 0; y < hratio; ++y)
	      pattern[gridbasex + x][gridbasey + y] = perlin(gridx + dec_lut[x], gridy + dec_lut[y]);
      }
}

void display()
{
  glColor3f(0, 0, 1);
  for(int frame = 0; ; ++frame)
    {
      frame %= wavePeriod;
      glBegin(GL_LINE_STRIP);
      for(int loc = 0; loc < waveSpan; ++loc)
	{
	  glVertex2f(loc, pattern[loc][frame] * waveMaxAmp + waveHorizon);
	}
      glEnd();
      glFlush();
      glClear(GL_COLOR_BUFFER_BIT);
      
      usleep(20000);
    }
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
