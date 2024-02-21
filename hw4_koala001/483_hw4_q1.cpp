#include <chrono>
#include <iostream>
#include <fstream>
#include <random>
#include <vector>

using namespace std;

// Part1: write type double binary square matrices
void writeMatrix(int n, std::ofstream &outfile)
{
  std::cout << "The output of different dimension" << n << endl;

  // Create a random number generator
  std::mt19937_64 rng(std::random_device{}());
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  // Create the matrix and fill it with random values
  std::vector<double> matrix(n * n);
  for (int i = 0; i < n * n; i++)
  {
    matrix[i] = dist(rng);
  }

  // Write the matrix to file in binary format
  auto begin = std::chrono::steady_clock::now();
  std::string dimension_num = std::to_string(n) + "dimension" + ".bin";
  std::ofstream outfileMatrix(dimension_num, std::ios::out | std::ios::binary);
  if (outfileMatrix.is_open())
  {
    outfileMatrix.write(reinterpret_cast<const char *>(matrix.data()), sizeof(double) * n * n);
    outfileMatrix.close();
  }
  else
  {
    std::cerr << "Failed to open file: matrix.bin" << std::endl;
  }
  auto end = std::chrono::steady_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
  double bandwidth = (sizeof(double) * n * n) / time.count() * 1e6;
  outfile << bandwidth << std::endl;
}

// Part2: read type double binary square matrices
void readMatrix(int n, std::ofstream &outfile)
{
  std::cout << "Read Matrices with dimension" << n << endl;
  // build the output file
  std::string dimension_num = std::to_string(n) + "dimension" + ".bin";
  std::ifstream input(dimension_num, std::ios::binary);
  if (!input)
  {
    std::cerr << "Error: could not open file for reading" << std::endl;
  }

  // Create a vector to store the matrix data
  std::vector<double> matrix(n * n);

  // Read the binary data into the vector
  auto begin = std::chrono::high_resolution_clock::now(); // start measuring time
  input.read(reinterpret_cast<char *>(matrix.data()), sizeof(double) * matrix.size());
  auto end = std::chrono::high_resolution_clock::now(); // end measuring time
  auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

  // Check if read was successful
  if (!input)
  {
    std::cerr << "Error: could not read file" << std::endl;
  }
  double bandwidth = (sizeof(double) * matrix.size()) / time.count() * 1e6;
  outfile << bandwidth << std::endl;
}

int main()
{
  int dimensions[] = {32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384};

  // Part1: write
  std::ofstream outfile_write_plot("part1_write.csv");
  outfile_write_plot << "bandwidth" << std::endl;
  // Write matrices to file and measure write time
  std::cout << "Part 1 of writing" << endl;
  for (int dimension : dimensions)
  {
    writeMatrix(dimension, outfile_write_plot);
  }
  outfile_write_plot.close();

  // Part2: read
  std::ofstream outfile_read_plot("part2_read.csv");
  outfile_read_plot << "bandwidth" << std::endl;
  // Read matrices from file and measure read time
  std::cout << "Part 2 of reading:" << endl;
  for (int dimension : dimensions)
  {
    readMatrix(dimension, outfile_read_plot);
  }

  return 0;
}