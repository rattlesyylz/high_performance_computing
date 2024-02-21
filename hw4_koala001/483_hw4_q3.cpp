#include <iostream>
#include <thread>
#include <cmath>
#include <chrono>
#include <mpi.h>

double f_prime(double x)
{
  return 1 / x - x / 4;
}

double riemann_sum(double a, double b, int n)
{
  double h = (b - a) / n;
  double sum = 0.0;
  for (int i = 0; i < n; ++i)
  {
    double x = a + i * h;
    sum += sqrt(1 + pow(f_prime(x), 2)) * h;
  }
  return sum;
}

int main(int argc, char *argv[])
{
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  double a = 1.0, b = 6.0;

  for (int num_partitions = 10; num_partitions <= 1e6; num_partitions *= 10)
  {
    double local_a = a + rank * (b - a) / size;
    double local_b = a + (rank + 1) * (b - a) / size;
    int local_n = num_partitions / size;
    double local_sum = riemann_sum(local_a, local_b, local_n);
    double global_sum;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
      double true_length = 6.16676;
      double log_error = std::log(std::abs(global_sum - true_value));
      std::cout << "Get Error: " << error << std::endl;
    }
  }

  MPI_Finalize();
  return 0;
}