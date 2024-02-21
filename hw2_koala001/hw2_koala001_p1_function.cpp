#include "hw2_koala001_p1_function.hpp"
#include <vector>
void daxpy(double a, const std::vector<double> &x, std::vector<double> &y)
{
  for (int i = 0; i < x.size(); i++)
  {
    y[i] += a * x[i];
  }
}