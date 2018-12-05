#include "image_utility.h"
#include <iostream>

void setPixel(Point p, Image& im, char c)
{
  im[im.size() - p.y - 1][p.x] = c;
}

void setOctPixel(Point p, Point center, Image& im, char c)
{
  setPixel(Point(p.x + center.x, p.y + center.y), im, c);
  setPixel(Point(p.y + center.x, p.x + center.y), im, c);
  setPixel(Point(p.y + center.x, -p.x + center.y), im, c);
  setPixel(Point(p.x + center.x, -p.y + center.y), im, c);
  
  setPixel(Point(-p.x + center.x, p.y + center.y), im, c);
  setPixel(Point(-p.y + center.x, p.x + center.y), im, c);
  setPixel(Point(-p.y + center.x, -p.x + center.y), im, c);
  setPixel(Point(-p.x + center.x, -p.y + center.y), im, c);
}

void outImage(const Image& im)
{
  for(const auto& line : im)
    {
      for(char pix : line)
	std::cout << pix << " ";
      std::cout << std::endl;
    }
}

void clearImage(Image& im, char c)
{
  for(auto& line : im)
    for(char& ele : line)
      ele = c;
}
