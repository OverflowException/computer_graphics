#ifndef _OBJECT_UTILITY_H
#define _OBJECT_UTILITY_H

#include <vector>
#include <utility>

struct Point
{
  int x;
  int y;
Point(int x = 0, int y = 0) : x(x), y(y){};
};

//This representation of Entity cannot deal with circle scaling
struct Entity
{
  typedef size_t VertIdx;
  typedef std::pair<VertIdx, VertIdx> Edge;
  typedef std::pair<VertIdx, int> Circle;
  typedef float Color[3];

  Color color;
  std::vector<Point> verts;
  std::vector<Edge> edges;
  std::vector<Circle> circles;

  inline void setColor(float r, float g, float b)
  {
    color[0] = r;
    color[1] = g;
    color[2] = b;
  }
  
  inline void addVert(Point v)
  {
    verts.push_back(v);
  }

  inline void addEdge(VertIdx id1, VertIdx id2)
  {
    edges.push_back(std::make_pair(id1, id2));
  }

  inline void addCircle(VertIdx idc, int r)
  {
    circles.push_back(std::make_pair(idc, r));
  }
};

#endif
