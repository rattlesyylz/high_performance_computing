#include <vector>
#include <stdexcept>
#include <chrono>
#include <iostream>
#include <random>
#include <fstream>
#include <cmath>
#include "mm_kij.hpp"

template <typename T>
void mm_kij(T a, const std::vector<T> &A, const std::vector<T> &B, T b, std::vector<T> &C, int m, int p, int n)
{
  if (A.size() != m * p || B.size() != p * n || C.size() != m * n)
  {
    throw std::invalid_argument("The num_cols and num_rows do not match.");
  }
  for (int k = 0; k < p; k++)
  {
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        C[j * m + i] = a * A[k * m + i] * B[j * p + k] + b * C[j * m + i];
      }
    }
  }
}
template void mm_kij<int>(int a, const std::vector<int> &A, const std::vector<int> &B, int b, std::vector<int> &C, int m, int p, int n);
template void mm_kij<float>(float a, const std::vector<float> &A, const std::vector<float> &B, float b, std::vector<float> &C, int m, int p, int n);
template void mm_kij<double>(double a, const std::vector<double> &A, const std::vector<double> &B, double b, std::vector<double> &C, int m, int p, int n);