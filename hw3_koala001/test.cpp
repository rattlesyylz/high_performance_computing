#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>
#include "hw3_header.hpp"
#include "mm_kij.hpp"
#include "mm_jki.hpp"

template <typename T>
int measure(const int ntrials, const std::string &exp_name,
            void (*func)(T a, const std::vector<T> &A, const std::vector<T> &B,
                         T b, std::vector<T> &C, int m, int p, int n))
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<T> dist(0.0, 1.0);
  for (int n = 2; n <= 512; n++)
  {
    T alpha = dist(gen);
    T beta = dist(gen);
    std::vector<T> A(n * n);
    std::vector<T> B(n * n);
    std::vector<T> C(n * n);
    for (int i = 0; i < A.size(); i++)
    {
      A[i] = dist(gen);
      B[i] = dist(gen);
      C[i] = dist(gen);
    }
    long double num_flops = static_cast<long double>(2. * n * n * n + 2. * n * n);
    long double time_in_ms = 0.0;

    // Test ntrails
    for (int t = 0; t < ntrials; t++)
    {
      auto begin = std::chrono::high_resolution_clock::now();
      try
      {
        func(alpha, A, B, beta, C, n, n, n);
      }
      catch (std::invalid_argument exception)
      {
        return 1;
      }
      auto end = std::chrono::high_resolution_clock::now();
      auto duration =
          std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
      time_in_ms +=
          (duration.count() * 1.e-3);
    }
    long double avg_time_ms =
        time_in_ms / static_cast<long double>(ntrials);
    long double mflops = num_flops / avg_time_ms;
    std::cout << mflops << std::endl;
  }
  return 0;
}
int main()
{
  int ntrials = 3;
  std::string optimization = "no-op";
#ifdef OPT
#endif
  return 0;
}
