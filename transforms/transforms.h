#ifndef _TRANSFORMS_H
#define _TRANSFORMS_H

#include "../utilities/point_utility.h"
#include <iostream>

typedef double TransMat2d [3][3];
typedef double TransMat3d [4][4];

template<typename Ms, typename Mr, typename D>
void matCopy(const Ms& src, Mr& dst, D r, D c)
{
  for(D row = 0; row < r; ++row)
    for(D col = 0; col < c; ++col)
      dst[row][col] = src[row][col];
}

void setIdentity2d(TransMat2d);
void setIdentity3d(TransMat3d);
void rotate2d(TransMat2d, Pointd center, double angle);
bool rotateAxis3d(TransMat3d mat, int axis, double angle);
void rotate3d(TransMat3d, Pointd axisp1, Pointd axisp2, double angle);
void scale2d(TransMat2d, Pointd pvt, double sx, double sy);
void scale3d(TransMat3d, Pointd pvt, double sx, double sy, double sz);
void translate2d(TransMat2d, double tx, double ty);
void translate3d(TransMat3d, double tx, double ty, double tz);

void compositeTrans2d(TransMat2d, TransMat2d, TransMat2d);
void compositeTrans3d(TransMat3d, TransMat3d, TransMat3d);

Pointd transform2d(TransMat2d, Pointd);
Pointd transform3d(TransMat3d, Pointd);

void showMat3x3(TransMat2d);
void showMat4x4(TransMat3d);

void cleanError3x3(TransMat2d, double threshold);
void cleanError4x4(TransMat3d, double threshold);

#endif
