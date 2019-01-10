#include <cmath>
#include "ortho.h"
#include "../transforms/transforms.h"

typedef double ViewMat3d [4][4];

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

//orient and horizon should be unit and perpendicular
void ortho3d(ViewMat3d mat, Pointd pos, Vec3d orient, Vec3d horizon)
{
  // //Unify orient
  // unify(orient);
  // //horizon's projection on unit orient
  // horizon = sub(horizon, mul(orient, dot(orient, horizon)));
  // unify(horizon);
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

  TransMat3d transMat;
  translate3d(transMat, -pos.x, -pos.y, -pos.z);
  
  compositeTrans3d(mat, transMat, mat);
}

