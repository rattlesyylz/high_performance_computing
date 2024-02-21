#include "hw2_koala001_p3_function.hpp"
#include <vector>
void dgemv(double a, const std::vector<std::vector<double> > &A, const std::vector<double> &x, double b, std::vector<double> &y)
{
  int m = A.size();
  int n = A[0].size();
  for (int i = 0; i < m; i++)
  {
    double Ax = 0.0;
    for (int j = 0; j < n; j++)
    {
      Ax += A[i][j] * x[j];
    }
    y[i] = a * Ax + b * y[i];
  }
}