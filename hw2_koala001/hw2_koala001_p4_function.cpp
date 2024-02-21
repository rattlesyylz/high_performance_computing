#include "hw2_koala001_p4_function.hpp"
#include <vector>
void dgemm(double a, const std::vector<std::vector<double> > &A, const std::vector<std::vector<double> > &B, double b, std::vector<std::vector<double> > &C)
{
  int m = A.size();
  int n = B[0].size();
  int p = A[0].size();
  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
    {
      double cij = 0.0;
      for (int k = 0; k < p; k++)
      {
        cij += A[i][k] * B[k][j];
      }
      C[i][j] = a * cij + b * C[i][j];
    }
  }
}