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
void transformEntity2d(const TransMat2d& mat, Entity<double>& ent)
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

