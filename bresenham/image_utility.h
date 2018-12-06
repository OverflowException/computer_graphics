#ifndef _IMAGE_UTILITY_H
#define _IMAGE_UTILITY_H

#include <vector>

struct Point
{
  int x;
  int y;
Point(int x = 0, int y = 0) : x(x), y(y){};
};

typedef std::vector<std::vector<char>> Image;

void setPixel(Point p, Image& im, char c);
void setOctPixel(Point p, Point center, Image& im, char c);
void setQuartPixel(Point p, Point center, Image& im, char c);

void outImage(const Image& im);
void clearImage(Image& im, char c);

#endif
