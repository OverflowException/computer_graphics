#include <cmath>

struct Point3d
{
  double x;
  double y;
  double z;
};

typedef Point3d Vec3d;

typedef double ViewMat3d [3][3];

Vec3d add(const Vec3d& v1, const Vec3d& v2)
{
  return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

Vec3d sub(const Vec3d& v1, const Vec3d& v2)
{
  return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

Vec3d mul(const Vec3d& v, double k)
{
  return {k * v.x, k * v.y, k * v.z};
}

Vec3d cross(const Vec3d& v1, const Vec3d& v2)
{
  return { v1.y * v2.z - v1.z * v2.y,
      v1.z * v2.x - v1.x * v2.z,
      v1.x * v2.y - v1.y * v2.x};
}

double dot(const Vec3d& v1, const Vec3d& v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

void unify(Vec3d& v)
{
  double d = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
  v.x /= d; v.y /= d; v.z /= d;
}

//orient and horizon dont necessarily be unit
//they are not necessarily perpendicular. Horizontal plane is determined by by these 2 vectors 
void ortho3d(ViewMat3d mat, Point3d pos, Vec3d orient, Vec3d horizon)
{
  //Unify orient
  unify(orient);
  //horizon's projection on unit orient
  horizon = sub(horizon, mul(orient, dot(orient, horizon)));
  unify(horizon);
  Vec3d vert = cross(horizon, orient);

  //////////////
  mat[0][0] = horizon.x;
  mat[0][1] = horizon.y;
  mat[0][2] = horizon.z;

  mat[1][0] = vert.x;
  mat[1][1] = vert.y;
  mat[1][2] = vert.z;

  mat[2][0] = orient.x;
  mat[2][1] = orient.y;
  mat[2][2] = orient.z;
  
}

