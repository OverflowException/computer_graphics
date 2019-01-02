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

//This representation of Entity cannot deal with circle scaling
template<typename T>
struct Entity
{
  typedef T coord_type;
  typedef Point_<coord_type> vert_type;
  typedef size_t vert_idx_type;
  typedef std::pair<vert_idx_type, vert_idx_type> edge_type;
  typedef std::pair<vert_idx_type, int> circle_type;
  typedef float color_type[3];

  color_type color;
  std::vector<vert_type> verts;
  std::vector<edge_type> edges;
  std::vector<circle_type> circles;

  inline void setColor(float r, float g, float b)
  {
    color[0] = r;
    color[1] = g;
    color[2] = b;
  }
  
  inline void addVert(vert_type v)
  {
    verts.push_back(v);
  }

  inline void addEdge(vert_idx_type id1, vert_idx_type id2)
  {
    edges.push_back(std::make_pair(id1, id2));
  }

  inline void addCircle(vert_idx_type idc, coord_type r)
  {
    circles.push_back(std::make_pair(idc, r));
  }
};

#endif
