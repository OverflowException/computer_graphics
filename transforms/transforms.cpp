#include "transforms.h"
#include <iostream>
#include <cmath>

void setIdentity2d(TransMat2d mat)
{
  for(int row = 0; row < 3; ++row)
    for(int col = 0; col < 3; ++col)
      mat[row][col] = (row == col);
}

void scale2d(TransMat2d mat, Pointd center, double sx, double sy)
{
  double xc = center.x;
  double yc = center.y;
  
  setIdentity2d(mat);
  mat[0][0] = sx;
  mat[0][2] = (1 - sx) * xc;
  mat[1][1] = sy;
  mat[1][2] = (1 - sy) * yc;
}

void rotate2d(TransMat2d mat, Pointd center, double angle)
{
  double xc = center.x;
  double yc = center.y;

  double rad = angle * M_PI / 180;
  double sine = sin(rad);
  double cosine = cos(rad);

  //Row 0
  mat[0][0] = cosine;
  mat[0][1] = -sine;
  mat[0][2] = (1 - cosine) * xc + sine * yc;
  //Row 1  
  mat[1][0] = sine;
  mat[1][1] = cosine;
  mat[1][2] = (1 - cosine) * yc - xc * sine;
  //Row 2
  mat[2][0] = mat[2][1] = 0;
  mat[2][2] = 1;  
}

void translate2d(TransMat2d mat, double tx, double ty)
{
  setIdentity2d(mat);
  mat[0][2] = tx;
  mat[1][2] = ty;
}

void setIdentity3d(TransMat3d mat)
{
  for(int row = 0; row < 4; ++row)
    for(int col = 0; col < 4; ++col)
      mat[row][col] = (row == col);
}

bool rotateAxis3d(TransMat3d mat, int axis, double angle)
{
  setIdentity3d(mat);
  double sine = sin(angle);
  double cosine = cos(angle);
  //The 4 indices that will be set to sine or cosine values
  int idx1 = 0, idx2 = 0;
  
  switch (axis)
    {
      //x axis
    case 0x001:
      idx1 = 1; idx2 = 2;
      break;
      
      //y axis
    case 0x010:
      idx1 = 0; idx2 = 2;
      break;
      
      //z axis
    case 0x100:
      idx1 = 0; idx2 = 1;
      break;
      
    default:
      return false;
      break;
    }

  mat[idx1][idx1] = cosine;
  mat[idx1][idx2] = -sine;
  mat[idx2][idx1] = sine;
  mat[idx2][idx2] = cosine;
  return true;
}

void rotate3d(TransMat3d mat, Pointd axisp1, Pointd axisp2, double angle)
{
  double x = axisp2.x - axisp1.x;
  double y = axisp2.y - axisp1.y;
  double z = axisp2.z - axisp1.z;

  unsigned char axisCode = 0;
  if(x != 0)
    axisCode |= 0x001;
  if(y != 0)
    axisCode |= 0x010;
  if(z != 0)
    axisCode |= 0x100;

  if(rotateAxis3d(mat, axisCode, angle))
    return;
  
  double x2 = x*x, y2 = y*y;
  double dxy = sqrt(x2  + y2);
  double d = sqrt(x2 + y2 + z*z);

  //prefix c stands for cosine, s stands for sine
  double ctheta = x / dxy, stheta = y / dxy;
  double cphi = z / d, sphi = dxy / d;

  //Generate a mat which rotate to Z axis
  TransMat3d mToAxis;
  setIdentity3d(mToAxis);
  mToAxis[0][0] = ctheta * cphi;
  mToAxis[0][1] = stheta * cphi;
  mToAxis[0][2] = -sphi;
  
  mToAxis[1][0] = -stheta;
  mToAxis[1][1] = ctheta;

  mToAxis[2][0] = ctheta * sphi;
  mToAxis[2][1] = stheta * sphi;
  mToAxis[2][2] = cphi;

  //Generate a mat which rotates around Z axis
  TransMat3d mAroundAxis;
  rotateAxis3d(mAroundAxis, 0x100, angle);

  //Rotate to Z, rotate around Z, rotate from Z
  setIdentity3d(mat);
  matMul(mToAxis, mat, mat, 4, 4, 4);
  matMul(mAroundAxis, mat, mat, int(4), int(4), int(4));
  
  mToAxis[0][1] = 0 - mToAxis[0][1];
  mToAxis[0][2] = 0 - mToAxis[0][2];
  mToAxis[1][0] = 0 - mToAxis[1][0];
  mToAxis[2][0] = 0 - mToAxis[2][0];

  matMul(mToAxis, mat, mat, 4, 4, 4);
}

void translate3d(TransMat3d mat, double tx, double ty, double tz)
{
  setIdentity3d(mat);
  mat[0][3] = tx;
  mat[1][3] = ty;
  mat[2][3] = tz;
}


void showMat3x3(TransMat2d mat)
{
  for(int row = 0; row < 3; ++row)
    {
      for(int col = 0; col < 3; ++col)
	std::cout << mat[row][col] << "\t";
      std::cout << std::endl;
    }
}


//This transform function cannot deal with scaling of circle
void transformEntity2d(TransMat2d mat, Entity<double>& ent)
{
  double x, y;
  for(Pointd& p : ent.verts)
    {
      x = p.x;
      y = p.y;
      p.x = mat[0][0] * x + mat[0][1] * y + mat[0][2];
      p.y = mat[1][0] * x + mat[1][1] * y + mat[1][2];
    }
}

