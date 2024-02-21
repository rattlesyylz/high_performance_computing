#include <vector>
#include <stdexcept>
#include <chrono>
#include <iostream>
#include <random>
#include <fstream>
#include <cmath>
#ifndef MM_KJI_HPP
#define MM_KJI_HPP

template <typename T>
void mm_kji(T a, const std::vector<T> &A, const std::vector<T> &B, T b, std::vector<T> &C, int m, int p, int n);

#endif