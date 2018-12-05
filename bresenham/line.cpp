#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <functional>
#include <unistd.h>

struct Point
{
  int x;
  int y;
  Point(int x = 0, int y = 0) : x(x), y(y){};
};

typedef std::vector<std::vector<char>> Image;

Image im;

void drawLine(Point p1, Point p2, std::function<void(Point)>);
void setPixel(Point p);
void outImage(const Image& im);
void clearImage(Image& im);

int main(int argc, char** argv)
{
  //Initialize image
  int w = 31;
  int h = 31;
  im.resize(h, std::vector<char>(w, ' '));

  Point p0(15, 15);
  Point pArr[16] =
    {
      {30, 15},
      {30, 20},
      {30, 30},
      {20, 30},
      {15, 30},
      {10, 30},
      {0, 30},
      {0, 20},
      {0, 15},
      {0, 10},
      {0, 0},
      {10, 0},
      {15, 0},
      {20, 0},
      {30, 0},
      {30, 10}
    };
  
  for(int idx = 0; ; ++idx)
    {
      idx %= 16;
      
      usleep(100000);
      system("clear");
      drawLine(p0, pArr[idx], setPixel);
      outImage(im);
      clearImage(im);
    }
  
  
  return 0;
}


//This is a table dealing with Flipping transformations
std::function<Point(Point)> flipTrans[4] =
  {
    [](Point p){return p;},
    [](Point p){return Point(p.x, -p.y);},
    [](Point p){return Point(p.y, p.x);},
    [](Point p){return Point(p.y, -p.x);}
  };

void drawLine(Point p1, Point p2, std::function<void(Point)> setPixel)
{
  
  //Make sure p1 is on the left, p2 is on the right
  if(p1.x > p2.x)
    std::swap(p1, p2);

  // //Initial pixel
  // setPixel(p1);
  
  int dy = p2.y - p1.y;
  int dx = p2.x - p1.x;

  int transIdx = 0;
    
  //All of the following transformation will not affct the left-right relative position of p1 and p2

  //Slope is negative, flip along X axis
  if(dy < 0)
    {
      p1.y = -p1.y;
      p2.y = -p2.y;
      dy = -dy;

      transIdx |= 0x01;
    }
  
  //abs(slope) > 1, flip along y=x axis
  if(abs(dy) > dx)
    {
      std::swap(p1.x, p1.y);
      std::swap(p2.x, p2.y);
      std::swap(dx, dy);

      transIdx |= 0x02;
    }
  
  int alpha, beta, criterion;
  
  //Initialize constants and criterion for iteration
  alpha = 2 * dy;
  beta = 2 * dy - 2 * dx;
  criterion = 2 * dy - dx;

  //Draw each pixel  
  for(int x = p1.x, y = p1.y; x < p2.x; ++x)
    {
      setPixel(flipTrans[transIdx](Point(x, y)));
      
      //Nearer to upper
      if(criterion > 0)
	{
	  ++y;
	  criterion += beta;
	}
      //Nearer to lower
      else
	criterion += alpha;
    }
  //One last point
  setPixel(flipTrans[transIdx](p2));
}

void outImage(const Image& im)
{
  for(const auto& line : im)
    {
      for(char pix : line)
	std::cout << pix;
      std::cout << std::endl;
    }
}

void clearImage(Image& im)
{
  for(auto& line : im)
    {
      for(char& ele : line)
	ele = ' ';
    }
}

void setPixel(Point p)
{
  im[im.size() - p.y - 1][p.x] = '*';
}

