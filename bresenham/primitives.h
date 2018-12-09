#ifndef _PRIMITIVES_H
#define _PRIMITIVES_H

#include "object_utility.h"

void drawLine(Point p1, Point p2);
void drawCircle(Point center, int radius);
void drawElipse(Point center, int rx, int ry);
void drawEntity(const Entity& ent);

#endif
