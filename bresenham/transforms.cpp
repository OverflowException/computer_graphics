#include "transforms.h"
#include <iostream>
#include <cmath>

void setIdentity2d(TransMat2d mat)
{
  for(int row = 0; row < 3; ++row)
    for(int col = 0; col < 3; ++col)
      mat[row][col] = (row == col);
}

void scale2d(TransMat2d mat, Point center, float sx, float sy)
{
  int xc = center.x;
  int yc = center.y;
  
  setIdentity2d(mat);
  mat[0][0] = sx;
  mat[0][2] = (1 - sx) * xc;
  mat[1][1] = sy;
  mat[1][2] = (1 - sy) * yc;
}

void rotate2d(TransMat2d mat, Point center, float angle)
{
  int xc = center.x;
  int yc = center.y;

  float rad = angle * M_PI / 180;
  float sine = sin(rad);
  float cosine = cos(rad);

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

void translate2d(TransMat2d mat, float tx, float ty)
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

//This transoform function cannot deal with scaling of circle
void transformEntity2d(const TransMat2d& mat, Entity& ent)
{
  float xf, yf;
  for(Point& p : ent.verts)
    {
      //To ensure floating point property
      xf = p.x;
      yf = p.y;
      p.x = mat[0][0] * xf + mat[0][1] * yf + mat[0][2];
      p.y = mat[1][0] * xf + mat[1][1] * yf + mat[1][2];
    }
}

