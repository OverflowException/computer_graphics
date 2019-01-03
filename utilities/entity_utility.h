#include "point_utility.h"
#include <utility>
#include <vector>

//This representation of Entity cannot deal with circle scaling
template<typename T>
struct Entity
{
  typedef T coord_type;
  typedef Point_<coord_type> vert_type;
  typedef size_t vert_idx_type;
  
  typedef struct
  {
    float r;
    float g;
    float b;
  }color_type;
  
  typedef struct
  {
    vert_idx_type start;
    vert_idx_type end;
    color_type color;
  }edge_type;
  //typedef std::pair<vert_idx_type, vert_idx_type> edge_type;

  std::vector<vert_type> verts;
  std::vector<edge_type> edges;
  
  inline void addVert(vert_type v)
  {
    verts.push_back(v);
  }

  inline void addEdge(vert_idx_type id1, vert_idx_type id2, color_type color)
  {
    edges.push_back({id1, id2, color});
  }
};
