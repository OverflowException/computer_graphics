#include <iostream>
#include "ortho.cpp"

using namespace std;

int main(int argc, char** argv)
{
  ViewMat3d view;
  ortho3d(view, {1, 1, 1}, {-1, -1, -1}, {1, 2, 0});

  for(int row = 0; row < 3; ++row)
    {
      for(int col = 0; col < 3; ++col)
	cout << view[row][col] << " ";
      cout << endl;
    }

}
