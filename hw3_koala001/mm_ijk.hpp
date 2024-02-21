#include <vector>
#include <stdexcept>
#include <chrono>
#include <iostream>
#include <random>
#include <fstream>
#include <cmath>
#ifndef MM_IJK_HPP
#define MM_IJK_HPP


template <typename T>
void mm_ijk(T a, const std::vector<T> &A, const std::vector<T> &B, T b, std::vector<T> &C, int m, int p, int n);

#endif
