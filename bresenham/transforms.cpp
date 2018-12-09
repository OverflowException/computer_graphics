#include "transforms.h"
#include <iostream>

void setIdentity(TransMat2d mat)
{
  for(int row = 0; row < 3; ++row)
    for(int col = 0; col < 3; ++col)
      mat[row][col] = (row == col);
}

void showMat(TransMat2d mat)
{
  for(int row = 0; row < 3; ++row)
    {
      for(int col = 0; col < 3; ++col)
	std::cout << mat[row][col] << "\t";
      std::cout << std::endl;
    }
}
