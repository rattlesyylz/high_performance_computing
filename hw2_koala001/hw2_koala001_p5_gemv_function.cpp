#include "hw2_koala001_p5_gemv_function.hpp"
#include <vector>
template <typename T>
void gemv(T a, const std::vector<std::vector<T>> &A, const std::vector<T> &x, T b, std::vector<T> &y)
{
  int m = A.size();
  int n = A[0].size();
  for (int i = 0; i < m; i++)
  {
    T Ax = 0;
    for (int j = 0; j < n; j++)
    {
      Ax += A[i][j] * x[j];
    }
    y[i] = a * Ax + b * y[i];
  }
}
template void gemv(double a, const std::vector<std::vector<double>> &A, const std::vector<double> &x, double b, std::vector<double> &y);
template void gemv(float a, const std::vector<std::vector<float>> &A, const std::vector<float> &x, float b, std::vector<float> &y);