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

//Rotate around axis. Rotation direction is the positive direction of corresponding axis
bool rotateAxis3d(TransMat3d mat, int axis, double angle)
{
  setIdentity3d(mat);
  double rad = angle * M_PI / 180;
  double sine = sin(rad);
  double cosine = cos(rad);
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
      idx1 = 2; idx2 = 0;
      break;
      
      //z axis
    case 0x100:
      idx1 = 0; idx2 = 1;
      break;
      
    default:
      return false;
    }

  mat[idx1][idx1] = cosine;
  mat[idx1][idx2] = -sine;
  mat[idx2][idx1] = sine;
  mat[idx2][idx2] = cosine;
  return true;
}

void rotate3d(TransMat3d mat, Pointd axisp1, Pointd axisp2, double angle)
{
  TransMat3d mToOrigin;
  translate3d(mToOrigin, -axisp1.x, -axisp1.y, -axisp1.z);
  
  double x = axisp2.x - axisp1.x;
  double y = axisp2.y - axisp1.y;
  double z = axisp2.z - axisp1.z;

  //Check if rotation axis is parallel to x, y or z
  int axisCode = 0;
  if(x != 0)
    {
      axisCode |= 0x001;
      if(x < 0)
	angle = -angle;
    }
  if(y != 0)
    {
      axisCode |= 0x010;
      if(y < 0)
	angle = -angle;
    }
  if(z != 0)
    {
      axisCode |= 0x100;
      if(z < 0)
	angle = -angle;
    }

  if(!rotateAxis3d(mat, axisCode, angle))
    {
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
      compositeTrans3d(mToAxis, mat, mat);
      compositeTrans3d(mAroundAxis, mat, mat);

      //Inverse matrix. Equivalent to transpose for diagonal matrix
      std::swap(mToAxis[0][1], mToAxis[1][0]);
      std::swap(mToAxis[0][2], mToAxis[2][0]);
      std::swap(mToAxis[1][2], mToAxis[2][1]);

      compositeTrans3d(mToAxis, mat, mat);
    }
  
  compositeTrans3d(mat, mToOrigin, mat);
  mToOrigin[0][3] = -mToOrigin[0][3];
  mToOrigin[1][3] = -mToOrigin[1][3];
  mToOrigin[2][3] = -mToOrigin[2][3];
  compositeTrans3d(mToOrigin, mat, mat);  
}

void translate3d(TransMat3d mat, double tx, double ty, double tz)
{
  setIdentity3d(mat);
  mat[0][3] = tx;
  mat[1][3] = ty;
  mat[2][3] = tz;
}

void scale3d(TransMat3d mat, Pointd pvt, double sx, double sy, double sz)
{
  std::cout << "3d scaling not yet implemented!" << std::endl;
}


void compositeTrans2d(TransMat2d m1, TransMat2d m2, TransMat2d mr)
{
  TransMat2d mtmp;
  for(int row = 0; row < 3; ++row)
    for(int col = 0; col < 3; ++col)
      {
	mtmp[row][col] = 0;
	for(int idx = 0; idx < 3; ++idx)
	  mtmp[row][col] += m1[row][idx] * m2[idx][col];
      }

  matCopy(mtmp, mr, 3, 3);
}


void compositeTrans3d(TransMat3d m1, TransMat3d m2, TransMat3d mr)
{
  TransMat3d mtmp;
  for(int row = 0; row < 4; ++row)
    for(int col = 0; col < 4; ++col)
      {
	mtmp[row][col] = 0;
	for(int idx = 0; idx < 4; ++idx)
	  mtmp[row][col] += m1[row][idx] * m2[idx][col];
      }

  matCopy(mtmp, mr, 4, 4);
}


Pointd transform2d(TransMat3d mat, Pointd p)
{
  return
    {p.x * mat[0][0] + p.y * mat[0][1] + mat[0][2],
      p.x * mat[1][0] + p.y * mat[1][1] + mat[1][2]};
}

Pointd transform3d(TransMat3d mat, Pointd p)
{
  return
    {p.x * mat[0][0] + p.y * mat[0][1] + p.z * mat[0][2] + mat[0][3],
      p.x * mat[1][0] + p.y * mat[1][1] + p.z * mat[1][2] + mat[1][3],
      p.x * mat[2][0] + p.y * mat[2][1] + p.z * mat[2][2] + mat[2][3]};
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

void showMat4x4(TransMat3d mat)
{
  for(int row = 0; row < 4; ++row)
    {
      for(int col = 0; col < 4; ++col)
	std::cout << mat[row][col] << "\t";
      std::cout << std::endl;
    }
}

void cleanError3x3(TransMat2d mat, double threshold)
{
  for(int row = 0; row < 3; ++row)
    for(int col = 0; col < 3; ++col)
      if(fabs(mat[row][col]) < threshold)
	mat[row][col] = 0.0;
}

void cleanError4x4(TransMat3d mat, double threshold)
{
  for(int row = 0; row < 4; ++row)
    for(int col = 0; col < 4; ++col)
      if(fabs(mat[row][col]) < threshold)
	mat[row][col] = 0.0;
}
