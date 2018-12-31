struct Point
{
  float x;
  float y;
  float z;
};

struct CurveCtrlPts
{
  Point data[4];
};

struct TessCurve
{
  int num;
  Point* data;
};

struct SurfCtrlPts
{
  Point data[4][4];
};

struct TessSurf
{
  int row;
  int col;
  Point* data;
};

inline float bernstein(float ct0, float ct1, float ct2, float ct3, float t)
{
  return (((ct3 - 3*ct2 + 3*ct1 - ct0)*t + (3*ct2 - 6*ct1 + 3*ct0))*t + 3*(ct1 - ct0))*t + ct0;
}

inline Point bernstein2D(const Point* ct, float t)
{
  return Point{bernstein(ct[0].x, ct[1].x, ct[2].x, ct[3].x, t),
      bernstein(ct[0].y, ct[1].y, ct[2].y, ct[3].y, t)};
}

inline Point bernstein3D(const Point* ct, float t)
{
  return Point{bernstein(ct[0].x, ct[1].x, ct[2].x, ct[3].x, t),
      bernstein(ct[0].y, ct[1].y, ct[2].y, ct[3].y, t),
      bernstein(ct[0].z, ct[1].z, ct[2].z, ct[3].z, t)};
}

TessCurve genBezierCurve(const CurveCtrlPts& ctp, int n)
{
  if(n <= 0)
    return TessCurve();
  
  TessCurve cvp = {n + 1, (Point*)malloc((n + 1) * sizeof(Point))};

  float step = 1 / (float)n;
  float t = step;

  for(int idx = 1; idx < cvp.num - 1; ++idx, t += step)
    cvp.data[idx] = bernstein2D(ctp.data, t);

  cvp.data[0] = ctp.data[0];
  cvp.data[n] = ctp.data[3];
  
  return cvp;
}

//h is the number of segments along control points' H direction 
//v is the number of segments along control points' V direction
TessSurf genBezierSurf(const SurfCtrlPts& ctp, int h, int v)
{
  if(v <= 0 || h <= 0)
    return TessSurf();

  TessSurf sfp = {v + 1, h + 1, (Point*)malloc((h + 1) * (v + 1) * sizeof(Point))};
  //A set of temporary control points along vertical direction
  Point v_tmp[4];

  float hstep = 1 / (float)h;
  float vstep = 1 / (float)v;
  float th = 0;
  float tv = 0;

  int row, col, idx;
  for(col = 0; col < sfp.col; ++col, th += hstep)
    {
      for(row = 0; row < 4; ++row)
	v_tmp[row] = bernstein3D(ctp.data[row], th);

      for(row = 0; row < sfp.row; ++row, tv += vstep)
	sfp.data[row * sfp.col + col] = bernstein3D(v_tmp, tv);
    }
    
  return sfp;
}


