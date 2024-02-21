#ifndef HW2_KOALA001_P2_FUNCTION_HPP
#define HW2_KOALA001_P2_FUNCTION_HPP

#include <vector>
#include <stdexcept>

void daxpy_unroll(const double a, const std::vector<double> &x, std::vector<double> &y, const int blockSize);

#endif
