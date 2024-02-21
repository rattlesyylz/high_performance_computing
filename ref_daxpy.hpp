// HW2 AMATH 483-583

#ifndef REF_DAXPY_HPP
#define REF_DAXPY_HPP
#include <vector>
void daxpy(double a, const std::vector<double> &x, std::vector<double> &y);

// Problem 2
void daxpy_unroll(double a, const std::vector<double> &x, std::vector<double> &y, int block_size);

#endif
