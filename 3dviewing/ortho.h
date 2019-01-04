#ifndef _ORTHO_H
#define _ORTHO_H

#include "../utilities/point_utility.h"
#include "../utilities/vec_utility.h"

typedef double ViewMat3d [4][4];

void setIdentityView(ViewMat3d mat);
Pointd view(ViewMat3d mat, Pointd p, double pfactor = 0, double width = 0, double height = 0);
void ortho3d(ViewMat3d mat, Pointd pos, Vec3d orient, Vec3d horizon);

#endif
