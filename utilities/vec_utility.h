#ifndef _VEC_UTILITY_H
#define _VEC_UTILITY_H

#include "point_utility.h"

typedef Pointd Vec3d;

inline Vec3d add(Vec3d v1, Vec3d v2)
{
  return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

inline Vec3d sub(Vec3d v1, Vec3d v2)
{
  return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

inline Vec3d neg(Vec3d v)
{
  return {-v.x, -v.y, -v.z};
}

inline Vec3d mul(Vec3d v, double k)
{
  return {k * v.x, k * v.y, k * v.z};
}

inline Vec3d cross(Vec3d v1, Vec3d v2)
{
  return { v1.y * v2.z - v1.z * v2.y,
      v1.z * v2.x - v1.x * v2.z,
      v1.x * v2.y - v1.y * v2.x};
}

inline double dot(Vec3d v1, Vec3d v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline void unify(Vec3d v)
{
  double d = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
  v.x /= d; v.y /= d; v.z /= d;
}

#endif
