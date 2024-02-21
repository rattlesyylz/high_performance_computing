// HW2 AMATH 483

#include "refBLAS.hpp"
#include <vector>
#include <stdexcept>

template <typename T>
void axpy(T alpha, const std::vector<T> &x, std::vector<T> &y)
{
    if (x.size() != y.size())
    {
        throw std::invalid_argument("Vector dimensions do not match.");
    }

    int n = x.size();

    for (int i = 0; i < n; i++)
    {
        y[i] += alpha * x[i];
    }
}

template void axpy<float>(float alpha, const std::vector<float> &x, std::vector<float> &y);
template void axpy<double>(double alpha, const std::vector<double> &x, std::vector<double> &y);
