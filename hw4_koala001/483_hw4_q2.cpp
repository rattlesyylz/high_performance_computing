#include <mutex>
#include <chrono>
#include <iostream>
#include <cmath>
#include <vector>
#include <thread>

double f_prime(double x)
{
  return 1 / x - x / 4;
}

void compute_partial_sum(double &sum, std::mutex &sum_mutex, double a, double h, int n, int num_threads, int i)
{
  double partial_sum = 0.0;
  int start = (n / num_threads) * i;
  int end = (i == num_threads - 1) ? n : (n / num_threads) * (i + 1);
  for (int j = start; j < end; ++j)
  {
    double x = a + j * h;
    partial_sum += sqrt(1 + pow(f_prime(x), 2));
  }
  partial_sum *= h;
  // Lock the mutex and update the sum variable
  sum_mutex.lock();
  sum += partial_sum;
  sum_mutex.unlock();
}

double parallel_riemann_sum(double a, double b, int n, int num_threads)
{
  double h = (b - a) / n;
  double sum = 0.0;
  std::vector<std::thread> threads(num_threads);

  // Mutex for protecting the sum variable
  std::mutex sum_mutex;

  // Spawn threads to compute partial sums
  for (int i = 0; i < num_threads; ++i)
  {
    threads[i] = std::thread(compute_partial_sum, std::ref(sum), std::ref(sum_mutex), a, h, n, num_threads, i);
  }
  // Wait for threads to finish
  for (int i = 0; i < num_threads; ++i)
  {
    threads[i].join();
  }
  return sum;
}

int main(int argc, char *argv[])
{
  const double a = 1.0;
  const double b = 6.0;

  if (argc != 3)
  {
    std::cerr << "Usage: " << argv[0] << " nthreads npoints" << std::endl;
    return 1;
  }

  const int num_threads = std::atoi(argv[1]);
  const int num_partitions = std::atoi(argv[2]);

  // Compute Riemann sum in parallel
  auto start = std::chrono::high_resolution_clock::now();
  double sum = parallel_riemann_sum(a, b, num_partitions, num_threads);
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  double elapsed_time = duration.count() * 1.e-9;
  double exact = 6.16676;
  double error = std::abs(sum - exact);

  std::cout << "time: " << elapsed_time << std::endl;
  std::cout << "error: " << error << std::endl;

  return 0;
}