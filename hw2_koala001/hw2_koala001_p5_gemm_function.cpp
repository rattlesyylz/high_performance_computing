#include "hw2_koala001_p5_gemm_function.hpp"
#include <vector>
template <typename T>
void gemm(T a, const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B, T b, std::vector<std::vector<T>> &C)
{
  int m = A.size();
  int n = B[0].size();
  int p = A[0].size();
  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
    {
      T cij = 0;
      for (int k = 0; k < p; k++)
      {
        cij += A[i][k] * B[k][j];
      }
      C[i][j] = a * cij + b * C[i][j];
    }
  }
}
template void gemm(float a, const std::vector<std::vector<float>> &A, const std::vector<std::vector<float>> &B, float b, std::vector<std::vector<float>> &C);
template void gemm(double a, const std::vector<std::vector<double>> &A, const std::vector<std::vector<double>> &B, double b, std::vector<std::vector<double>> &C);