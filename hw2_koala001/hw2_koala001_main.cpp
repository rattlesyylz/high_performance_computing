#include "hw2_koala001_p1_function.hpp"
#include "hw2_koala001_p2_function.hpp"
#include "hw2_koala001_p3_function.hpp"
#include "hw2_koala001_p4_function.hpp"
#include "hw2_koala001_p5_axpy_function.hpp"
#include "hw2_koala001_p5_gemv_function.hpp"
#include "hw2_koala001_p5_gemm_function.hpp"
#include <iostream>
#include <chrono>
#include <fstream>
#include <random>
#include <vector>

// Function to test Problem 1
void p1_test_function()
{
  // set output file
  std::ofstream output_file("output1.csv");
  output_file << "n,avgerage_flops\n";

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  int ntrials = 100;
  std::vector<double> durations_trails(ntrials);
  std::vector<double> flops_trails(ntrials);

  for (int num = 2; num <= 1024; num++)
  {
    long double flop_count = static_cast<long double>(2 * num - 1);

    for (int i = 0; i < ntrials; i++)
    {
      double a = dist(gen);
      std::vector<double> x(num);
      std::vector<double> y(num);

      for (int j = 0; j < x.size(); j++)
      {
        x[j] = dist(gen);
        y[j] = dist(gen);
      }

      auto start = std::chrono::high_resolution_clock::now();
      daxpy(a, x, y);
      auto stop = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

      durations_trails[i] = static_cast<double>(duration.count());
      flops_trails[i] = flop_count / (durations_trails[i] * 1e-9) / (1e6);
    }

    double avgerage_durations = std::accumulate(durations_trails.begin(), durations_trails.end(), 0.0) / ntrials;
    double avgerage_flops = std::accumulate(flops_trails.begin(), flops_trails.end(), 0.0) / ntrials;

    output_file << num << "," << avgerage_flops << "\n";

    std::cout << "The average time given by code segment in nanoseconds is " << avgerage_durations << std::endl;
    std::cout << "The average axpy performance of MFLOPs is " << avgerage_flops << std::endl;
  }
  output_file.close();
}

// Function to test Problem 2
void p2_test_function()
{
  // set output file
  std::ofstream output_file("output2.csv");
  output_file << "block_size,avgerage_flops\n";

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  int n = 2048;
  int ntrials = 100;
  std::vector<double> durations_trails(ntrials);
  std::vector<double> flops_trails(ntrials);
  std::vector<int> block_size_vector;

  for (int block_size : block_size_vector)
  {
    long double flop_count = static_cast<long double>(2 * n - 1);

    for (int i = 0; i < ntrials; i++)
    {
      double a = dist(gen);
      std::vector<double> x(n);
      std::vector<double> y(n);

      for (int j = 0; j < x.size(); j++)
      {
        x[j] = dist(gen);
        y[j] = dist(gen);
      }

      auto start = std::chrono::high_resolution_clock::now();
      daxpy_unroll(a, x, y, block_size);
      auto stop = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

      durations_trails[i] = static_cast<double>(duration.count());
      flops_trails[i] = flop_count / (durations_trails[i] * 1e-9) / (1e6);
    }

    double avgerage_durations = std::accumulate(durations_trails.begin(), durations_trails.end(), 0.0) / ntrials;
    double avgerage_flops = std::accumulate(flops_trails.begin(), flops_trails.end(), 0.0) / ntrials;

    output_file << block_size << "," << avgerage_flops << "\n";

    std::cout << "The average time given by code segment in nanoseconds is " << avgerage_durations << std::endl;
    std::cout << "The average axpy performance of MFLOPs is " << avgerage_flops << std::endl;
  }
  output_file.close();
}

// Function to test Problem 3
void p3_test_function()
{
  // set output file
  std::ofstream output_file("output3.csv");
  output_file << "n,avgerage_flops\n";

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  int ntrials = 3;
  std::vector<double> durations_trails(ntrials);
  std::vector<double> flops_trails(ntrials);

  for (int num = 2; num <= 1024; num++)
  {
    long double flop_count = static_cast<long double>(2 * num * num - num);

    for (int i = 0; i < ntrials; i++)
    {
      double a = dist(gen);
      double b = dist(gen);
      std::vector<std::vector<double> > A(num, std::vector<double>(num));
      std::vector<double> x(num);
      std::vector<double> y(num);

      for (int j = 0; j < num; j++)
      {
        for (int k = 0; k < num; k++)
        {
          A[j][k] = dist(gen);
        }
        x[j] = dist(gen);
        y[j] = dist(gen);
      }

      auto start = std::chrono::high_resolution_clock::now();
      dgemv(a, A, x, b, y);
      auto stop = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

      durations_trails[i] = static_cast<double>(duration.count());
      flops_trails[i] = flop_count / (durations_trails[i] * 1e-9) / (1e6);
    }

    double avgerage_durations = std::accumulate(durations_trails.begin(), durations_trails.end(), 0.0) / ntrials;
    double avgerage_flops = std::accumulate(flops_trails.begin(), flops_trails.end(), 0.0) / ntrials;

    output_file << num << "," << avgerage_flops << "\n";

    std::cout << "The average time given by code segment in nanoseconds is " << avgerage_durations << std::endl;
    std::cout << "The average axpy performance of MFLOPs is " << avgerage_flops << std::endl;
  }
  output_file.close();
}

// Function to test Problem 4
void p4_test_function()
{
  // set output file
  std::ofstream output_file("output4.csv");
  output_file << "n,avgerage_flops\n";

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  int ntrials = 3;
  std::vector<double> durations_trails(ntrials);
  std::vector<double> flops_trails(ntrials);

  for (int num = 2; num <= 1024; num++)
  {
    long double flop_count = static_cast<long double>(2 * num * num * num + 2 * num * num);

    for (int i = 0; i < ntrials; i++)
    {
      double a = dist(gen);
      double b = dist(gen);
      std::vector<std::vector<double> > A(num, std::vector<double>(num));
      std::vector<std::vector<double> > B(num, std::vector<double>(num));
      std::vector<std::vector<double> > C(num, std::vector<double>(num));

      for (int j = 0; j < num; j++)
      {
        for (int k = 0; k < num; k++)
        {
          A[j][k] = dist(gen);
          B[j][k] = dist(gen);
          C[j][k] = dist(gen);
        }
      }

      auto start = std::chrono::high_resolution_clock::now();
      dgemm(a, A, B, b, C);
      auto stop = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

      durations_trails[i] = static_cast<double>(duration.count());
      flops_trails[i] = flop_count / (durations_trails[i] * 1e-9) / (1e6);
    }

    double avgerage_durations = std::accumulate(durations_trails.begin(), durations_trails.end(), 0.0) / ntrials;
    double avgerage_flops = std::accumulate(flops_trails.begin(), flops_trails.end(), 0.0) / ntrials;

    output_file << num << "," << avgerage_flops << "\n";

    std::cout << "The average time given by code segment in nanoseconds is " << avgerage_durations << std::endl;
    std::cout << "The average axpy performance of MFLOPs is " << avgerage_flops << std::endl;
  }
  output_file.close();
}

// Function to test Problem 5: axpy function
void p5_test_axpy_function()
{
  // set output file
  std::ofstream output_file("output5_1.csv");
  output_file << "n,avgerage_flops\n";

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dist(0.0, 1.0);

  int ntrials = 100;
  std::vector<double> durations_trails(ntrials);
  std::vector<double> flops_trails(ntrials);

  for (int num = 2; num <= 1024; num++)
  {
    long double flop_count = static_cast<long double>(2 * num - 1);

    for (int i = 0; i < ntrials; i++)
    {
      float a = dist(gen);
      std::vector<float> x(num);
      std::vector<float> y(num);

      for (int j = 0; j < x.size(); j++)
      {
        x[j] = dist(gen);
        y[j] = dist(gen);
      }

      auto start = std::chrono::high_resolution_clock::now();
      axpy(a, x, y);
      auto stop = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

      durations_trails[i] = static_cast<double>(duration.count());
      flops_trails[i] = flop_count / (durations_trails[i] * 1e-9) / (1e6);
    }

    double avgerage_durations = std::accumulate(durations_trails.begin(), durations_trails.end(), 0.0) / ntrials;
    double avgerage_flops = std::accumulate(flops_trails.begin(), flops_trails.end(), 0.0) / ntrials;

    output_file << num << "," << avgerage_flops << "\n";

    std::cout << "The average time given by code segment in nanoseconds is " << avgerage_durations << std::endl;
    std::cout << "The average axpy performance of MFLOPs is " << avgerage_flops << std::endl;
  }
  output_file.close();
}

// Function to test Problem 5: gemm function
void p5_test_gemm_function()
{
  // set output file
  std::ofstream output_file("output5_2.csv");
  output_file << "n,avgerage_flops\n";

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dist(0.0, 1.0);

  int ntrials = 3;
  std::vector<double> durations_trails(ntrials);
  std::vector<double> flops_trails(ntrials);

  for (int num = 2; num <= 1024; num++)
  {
    long double flop_count = static_cast<long double>(2 * num * num * num + 2 * num * num);

    for (int i = 0; i < ntrials; i++)
    {
      float a = dist(gen);
      float b = dist(gen);
      std::vector<std::vector<float> > A(num, std::vector<float>(num));
      std::vector<std::vector<float> > B(num, std::vector<float>(num));
      std::vector<std::vector<float> > C(num, std::vector<float>(num));

      for (int j = 0; j < num; j++)
      {
        for (int k = 0; k < num; k++)
        {
          A[j][k] = dist(gen);
          B[j][k] = dist(gen);
          C[j][k] = dist(gen);
        }
      }

      auto start = std::chrono::high_resolution_clock::now();
      gemm(a, A, B, b, C);
      auto stop = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

      durations_trails[i] = static_cast<double>(duration.count());
      flops_trails[i] = flop_count / (durations_trails[i] * 1e-9) / (1e6);
    }

    double avgerage_durations = std::accumulate(durations_trails.begin(), durations_trails.end(), 0.0) / ntrials;
    double avgerage_flops = std::accumulate(flops_trails.begin(), flops_trails.end(), 0.0) / ntrials;

    output_file << num << "," << avgerage_flops << "\n";

    std::cout << "The average time given by code segment in nanoseconds is " << avgerage_durations << std::endl;
    std::cout << "The average gemm performance of MFLOPs is " << avgerage_flops << std::endl;
  }
  output_file.close();
}

void p5_test_gemv_function()
{
  // set output file
  std::ofstream output_file("output5_3.csv");
  output_file << "n,avgerage_flops\n";

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dist(0.0, 1.0);

  int ntrials = 3;
  std::vector<double> durations_trails(ntrials);
  std::vector<double> flops_trails(ntrials);

  for (int num = 2; num <= 1024; num++)
  {
    long double flop_count = static_cast<long double>(2 * num * num - num);

    for (int i = 0; i < ntrials; i++)
    {
      float a = dist(gen);
      float b = dist(gen);
      std::vector<std::vector<float> > A(num, std::vector<float>(num));
      std::vector<float> x(num);
      std::vector<float> y(num);

      for (int j = 0; j < num; j++)
      {
        for (int k = 0; k < num; k++)
        {
          A[j][k] = dist(gen);
        }
        x[j] = dist(gen);
        y[j] = dist(gen);
      }

      auto start = std::chrono::high_resolution_clock::now();
      gemv(a, A, x, b, y);
      auto stop = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

      durations_trails[i] = static_cast<double>(duration.count());
      flops_trails[i] = flop_count / (durations_trails[i] * 1e-9) / (1e6);
    }

    double avgerage_durations = std::accumulate(durations_trails.begin(), durations_trails.end(), 0.0) / ntrials;
    double avgerage_flops = std::accumulate(flops_trails.begin(), flops_trails.end(), 0.0) / ntrials;

    output_file << num << "," << avgerage_flops << "\n";

    std::cout << "The average time given by code segment in nanoseconds is " << avgerage_durations << std::endl;
    std::cout << "The average gevm performance of MFLOPs is " << avgerage_flops << std::endl;
  }
  output_file.close();
}

int main()
{
  // p1_test_function();
  // p2_test_function();
  // p3_test_function();
  // p4_test_function();
  p5_test_axpy_function();
  p5_test_gemm_function();
  p5_test_gemv_function();
  return 0;
}
