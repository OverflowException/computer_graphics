#ifndef _TRANSFORMS_H
#define _TRANSFORMS_H

#include "object_utility.h"

typedef double TransMat2d [3][3];
typedef double TransMat3d [4][4];

template<typename M, typename D>
void matCopy(M src, M dst, D r, D c)
{
  for(D row = 0; row < r; ++row)
    for(D col = 0; col < c; ++col)
      dst[row][col] = src[row][col];
}

template<typename M, typename D>
void matMul(M m1, M m2, M mr, D r1, D c2, D common)
{
  M mtmp;
  for(D row = 0; row < r1; ++row)
    for(D col = 0; col < c2; ++col)
      {
	mtmp[row][col] = 0;
	decltype(mtmp[row][col])& ref = mtmp[row][col];
	for(D idx = 0; idx < common; ++idx)
	  ref += m1[row][idx] * m2[idx][col];
      }

  //To support in-place input matrices
  matCopy(mtmp, mr, r1, c2);
}

void setIdentity2d(TransMat2d);

void rotate2d(TransMat2d, Pointd center, double angle);
void scale2d(TransMat2d, Pointf pvt, double sx, double sy);
void translate2d(TransMat2d, double tx, double ty);

bool rotateAxis3d(TransMat3d mat, int axis, double angle);
void rotate3d(TransMat3d mat, Pointd axisp1, Pointd axisp2, double angle);

void showMat3x3(TransMat2d);

void transformEntity2d(TransMat2d mat, Entity<double>& ent);

#endif
