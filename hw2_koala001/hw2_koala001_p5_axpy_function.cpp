#include "hw2_koala001_p5_axpy_function.hpp"
#include <vector>
template <typename T>
void axpy(T alpha, const std::vector<T> &x, std::vector<T> &y)
{
  for (int i = 0; i < x.size(); i++)
  {
    y[i] += alpha * x[i];
  }
}
template void axpy(double alpha, const std::vector<double> &x, std::vector<double> &y);
template void axpy(float alpha, const std::vector<float> &x, std::vector<float> &y);