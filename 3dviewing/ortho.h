#ifndef _ORTHO_H
#define _ORTHO_H

#include "../utilities/point_utility.h"

typedef Pointd Vec3d;
typedef double ViewMat3d [4][4];

Vec3d add(const Vec3d& v1, const Vec3d& v2);
Vec3d sub(const Vec3d& v1, const Vec3d& v2);
Vec3d mul(const Vec3d& v, double k);
Vec3d cross(const Vec3d& v1, const Vec3d& v2);
double dot(const Vec3d& v1, const Vec3d& v2);
void unify(Vec3d& v);
void setIdentityView(ViewMat3d mat);
Pointd view(ViewMat3d mat, Pointd p, double pfactor = 0, double width = 0, double height = 0);
void ortho3d(ViewMat3d mat, Pointd pos, Vec3d orient, Vec3d horizon);

#endif
