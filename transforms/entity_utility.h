#include "point_utility.h"

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
