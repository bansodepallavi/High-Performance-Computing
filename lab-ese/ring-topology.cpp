#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data = 33;
    if (rank != 0)
    {
        MPI_Recv(&data, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received data %d from process %d\n", rank, data, rank - 1);
    }
    MPI_Send(&data, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
    printf("process %d sent %d to process %d \n", rank, data, (rank + 1) % size);
    if (rank == 0)
    {
        MPI_Recv(&data, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received data %d from process %d\n", rank, data, size - 1);
    }
    MPI_Finalize();
}
