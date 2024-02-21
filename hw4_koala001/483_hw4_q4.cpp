#include <cmath>
#include <mpi.h>
#include <vector>
#include <cstring>
#include <iostream>
#include <chrono>
#define MIN_SIZE 8
#define MAX_SIZE (128 * 1024 * 1024)

template <typename T>
void my_broadcast(T *data, int count, int root, MPI_Comm comm)
{
  int rank, size;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &size);

  if (rank == root)
  {
    for (int i = 0; i < size; i++)
    {
      if (i != root)
      {
        MPI_Send(data, count, MPI_BYTE, i, 0, comm);
      }
    }
  }
  else
  {
    MPI_Recv(data, count, MPI_BYTE, root, 0, comm, MPI_STATUS_IGNORE);
  }
  MPI_Barrier(comm);
}

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);

  int root = 0;
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  for (int msg_size = 8; msg_size <= 128 * 1024 * 1024; msg_size *= 2)
  {
    std::vector<char> message(msg_size);
    if (rank == 0)
    {
      std::memset(message.data(), 'a', msg_size);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    double t_start_mpi = MPI_Wtime();
    MPI_Bcast(message.data(), msg_size, MPI_BYTE, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    double t_end_mpi = MPI_Wtime();
    double bcast_bandwidth = msg_size / (t_end_mpi - t_start_mpi);
    MPI_Barrier(MPI_COMM_WORLD);
    double t_start_my = MPI_Wtime();
    my_broadcast(message.data(), msg_size, root, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    double t_end_my = MPI_Wtime();
    double my_bandwidth = msg_size / (t_end_my - t_start_my);

    if (rank == root)
    {
      std::cout << "Size: " << msg_size << " bytes" << std::endl;
      std::cout << "Broadcast: " << my_bandwidth << " bytes per sec" << std::endl;
      std::cout << "Bcast_of_MPI: " << bcast_bandwidth << " bytes per sec" << std::endl;
      std::cout << std::endl;
    }
  }

  MPI_Finalize();
  return 0;
}