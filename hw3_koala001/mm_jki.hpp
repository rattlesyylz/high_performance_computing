#include <vector>
#include <stdexcept>
#include <chrono>
#include <iostream>
#include <random>
#include <fstream>
#include <cmath>
#ifndef MM_JKI_HPP
#define MM_JKI_HPP


template <typename T>
void mm_jki(T a, const std::vector<T> &A, const std::vector<T> &B, T b, std::vector<T> &C, int m, int p, int n);

#endif