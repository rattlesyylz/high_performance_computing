#include <vector>
#include <stdexcept>
#include <chrono>
#include <iostream>
#include <random>
#include <fstream>
#include <cmath>
#include "mm_jik.hpp"

template <typename T>
void mm_jik(T a, const std::vector<T> &A, const std::vector<T> &B, T b, std::vector<T> &C, int m, int p, int n)
{
  if (A.size() != m * p || B.size() != p * n || C.size() != m * n)
  {
    throw std::invalid_argument("The num_cols and num_rows do not match.");
  }
  for (int j = 0; j < n; j++)
  {
    for (int i = 0; i < m; i++)
    {
      T ans = 0.0;
      for (int k = 0; k < p; k++)
      {
        ans += a * A[i + k * m] * B[k + j * p];
      }
      C[i + j * m] = ans + b * C[i + j * m];
    }
  }
}
template void mm_jik<int>(int a, const std::vector<int> &A, const std::vector<int> &B, int b, std::vector<int> &C, int m, int p, int n);
template void mm_jik<float>(float a, const std::vector<float> &A, const std::vector<float> &B, float b, std::vector<float> &C, int m, int p, int n);
template void mm_jik<double>(double a, const std::vector<double> &A, const std::vector<double> &B, double b, std::vector<double> &C, int m, int p, int n);