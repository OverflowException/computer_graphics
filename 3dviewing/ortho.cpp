#include <cmath>
#include "ortho.h"
#include "../utilities/point_utility.h"

typedef Pointd Vec3d;

typedef double ViewMat3d [4][4];

Vec3d add(const Vec3d& v1, const Vec3d& v2)
{
  return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

Vec3d sub(const Vec3d& v1, const Vec3d& v2)
{
  return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

Vec3d mul(const Vec3d& v, double k)
{
  return {k * v.x, k * v.y, k * v.z};
}

Vec3d cross(const Vec3d& v1, const Vec3d& v2)
{
  return { v1.y * v2.z - v1.z * v2.y,
      v1.z * v2.x - v1.x * v2.z,
      v1.x * v2.y - v1.y * v2.x};
}

double dot(const Vec3d& v1, const Vec3d& v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

void unify(Vec3d& v)
{
  double d = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
  v.x /= d; v.y /= d; v.z /= d;
}

void setIdentityView(ViewMat3d mat)
{
  for(int row = 0; row < 4; ++row)
    for(int col = 0; col < 4; ++col)
      mat[row][col] = (row == col);
}

//Perspective scaling cannot be represented linearly, thus cannot be multiplied into view matrix
Pointd view(ViewMat3d mat, Pointd p, double pfactor, double width, double height)
{ 
  double coord[3];
  for(int row = 0; row < 3; ++row)
    coord[row] = p.x * mat[row][0] + p.y * mat[row][1] + p.z * mat[row][2] + mat[row][3];

  if(width == 0 || height == 0)
    return {coord[0], coord[1], coord[2]};
  else
    {
      double scale = 2 * pfactor * coord[2];
      return {
	coord[0] * width / (width +  scale),
	  coord[1] * height / (height + scale),
	  coord[2]};
    }
  
}

//orient and horizon dont necessarily be unit
//they are not necessarily perpendicular. Horizontal plane is determined by by these 2 vectors 
void ortho3d(ViewMat3d mat, Pointd pos, Vec3d orient, Vec3d horizon)
{
  //Unify orient
  unify(orient);
  //horizon's projection on unit orient
  horizon = sub(horizon, mul(orient, dot(orient, horizon)));
  unify(horizon);
  Vec3d vert = cross(horizon, orient);

  setIdentityView(mat);
  //Camera orientation
  mat[0][0] = horizon.x;
  mat[0][1] = horizon.y;
  mat[0][2] = horizon.z;

  mat[1][0] = vert.x;
  mat[1][1] = vert.y;
  mat[1][2] = vert.z;

  mat[2][0] = orient.x;
  mat[2][1] = orient.y;
  mat[2][2] = orient.z;

  //Camera position
  pos = view(mat, pos);
  mat[0][3] = -pos.x;
  mat[1][3] = -pos.y;
  mat[2][3] = -pos.z;
}

