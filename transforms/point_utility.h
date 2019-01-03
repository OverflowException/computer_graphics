#ifndef _OBJECT_UTILITY_H
#define _OBJECT_UTILITY_H

#include <vector>
#include <utility>
#include <cmath>


template<typename T>
struct Point_;

typedef Point_<int> Pointi;
typedef Point_<float> Pointf;
typedef Point_<double> Pointd;


template<typename T>
struct Point_
{
  typedef T coord_type;
  
  coord_type x;
  coord_type y;
  coord_type z;
  Point_(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z){};
  
  template<typename Tt>
  Point_(const Point_<Tt>& p)
  {
    _Point_(p, coord_type());
  }

  void _Point_(const Pointf& p, int)
  {
    this->x = round(double(p.x));
    this->y = round(double(p.y));
    this->z = round(double(p.z));
  }

  void _Point_(const Pointd& p, int)
  {
    this->x = round(p.x);
    this->y = round(p.y);
    this->z = round(p.z);
  }

  template<typename Tt, typename Tn>
  void _Point_(const Point_<Tt>& p, Tn)
  {
    this->x = p.x;
    this->y = p.y;
    this->z = p.z;
  }
  
};

#endif
