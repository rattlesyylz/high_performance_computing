// HW2 AMATH 483

#include "refBLAS.hpp"
#include <vector>
#include <stdexcept>
void daxpy(double a, const std::vector<double> &x, std::vector<double> &y)
{
    int n = x.size();
    if (y.size() != n)
    {
        throw std::invalid_argument("Vector dimensions do not match");
    }

    for (int i = 0; i < n; i++)
    {
        y[i] = a * x[i] + y[i];
    }
}

// void daxpy_unroll(const double a, const vector<double>& x, vector<double>& y, const int blockSize, const int unrollDepth) {
void daxpy_unroll(const double a, const std::vector<double> &x, std::vector<double> &y, const int blockSize)
{
    int unrollDepth = 4;
    const int n = x.size();
    if (y.size() != n)
    {
        throw std::invalid_argument("Vector dimensions do not match");
    }
    const int nBlocks = n / blockSize;

    // Loop over blocks of size blockSize
    for (int iBlock = 0; iBlock < nBlocks; iBlock++)
    {
        const int blockStart = iBlock * blockSize;
        const int blockEnd = blockStart + blockSize;

        // Compute unrollDepth iterations at a time
        for (int i = blockStart; i < blockEnd; i += unrollDepth)
        {
            const int limit = std::min(i + unrollDepth, blockEnd);
            for (int j = i; j < limit; j++)
            {
                y[j] += a * x[j];
            }
        }
    }

    // Compute remaining elements
    for (int i = nBlocks * blockSize; i < n; i++)
    {
        y[i] += a * x[i];
    }
}

void daxpy(double a, const std::vector<double> &x, std::vector<double> &y);
void daxpy_unroll(double a, const std::vector<double> &x, std::vector<double> &y, int block_size);
