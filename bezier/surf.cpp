#include <iostream>
#include "bezier.cpp"

using namespace std;

int main(int argc, char** argv)
{
  SurfCtrlPts cpts = 
    {
      {
	{{10, 10, 0}, {20, 20, 40}, {25, 40, 50}, {35, 30, 10}},
	{{10, 10, 0}, {20, 20, 40}, {25, 40, 50}, {35, 30, 10}},
	{{10, 10, 0}, {20, 20, 40}, {25, 40, 50}, {35, 30, 10}},
	{{10, 10, 0}, {20, 20, 40}, {25, 40, 50}, {35, 30, 10}}
      }
    };

  TessSurf surf = genBezierSurf(cpts, 5, 5);

  //Show surface points
  for(int r = 0; r < surf.row; ++r)
    {
      for(int c = 0; c < surf.col; ++c)
	{
	  int idx = r * surf.col + c;
	  cout << "(" << surf.data[idx].x  << ", " << surf.data[idx].y << ", " << surf.data[idx].z << ") ";
	}
      cout << endl;
    }
  
  return 0;
}
