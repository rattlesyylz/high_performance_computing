#ifndef HW2_KOALA001_P5_GEMM_FUNCTION_HPP
#define HW2_KOALA001_P5_GEMM_FUNCTION_HPP
#include <vector>
template <typename T>
void gemm(T a, const std::vector<std::vector<T> > &A, const std::vector<std::vector<T> > &B, T b, std::vector<std::vector<T> > &C);
#endif