#ifndef HW2_KOALA001_P5_GEMV_FUNCTION_HPP
#define HW2_KOALA001_P5_GEMV_FUNCTION_HPP
#include <vector>
template <typename T>
void gemv(T a, const std::vector<std::vector<T> > &A, const std::vector<T> &x, T b, std::vector<T> &y);
#endif