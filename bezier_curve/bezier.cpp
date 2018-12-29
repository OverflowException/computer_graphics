struct Point
{
  float x;
  float y;
};

struct ControlPoints
{
  Point data[4];
};

struct CurvePoints
{
  int num;
  Point* data;
};

inline float bezierUtil(float ct0, float ct1, float ct2, float ct3, float t)
{
  return (((ct3 - 3*ct2 + 3*ct1 - ct0)*t + (3*ct2 - 6*ct1 + 3*ct0))*t + 3*(ct1 - ct0))*t + ct0;
}

CurvePoints genBezier(const ControlPoints& ctp, int n)
{
  if(n <= 0)
    return CurvePoints();
  
  CurvePoints cvp = {n + 1, (Point*)malloc((n + 1) * sizeof(Point))};

  float step = 1 / (float)n;
  float t = step;

  for(int idx = 1; idx < cvp.num - 1; ++idx, t += step)
    {
      cvp.data[idx].x = bezierUtil(ctp.data[0].x, ctp.data[1].x, ctp.data[2].x, ctp.data[3].x, t);
      cvp.data[idx].y = bezierUtil(ctp.data[0].y, ctp.data[1].y, ctp.data[2].y, ctp.data[3].y, t);
    }
  cvp.data[0] = ctp.data[0];
  cvp.data[n] = ctp.data[3];
  
  return cvp;
}

