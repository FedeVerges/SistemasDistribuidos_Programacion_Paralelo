#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"
#include <unistd.h>
int main(int argc, char *argv[])
{
    int my_rank;
    int n;
    MPI_Init(&argc, &argv);
    char message[50], recieved[50];
    strcpy(message, "");
    MPI_Status status;

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    if (my_rank == 0)
    {
        strcpy(message, "Stop");

        for (int i = 1; i < world_size; i += 1)
        {
            for (int i = 0; i < 999999990; i++)
            {
            }
            printf("Enviando msj al proceso %d \n", i);
            MPI_Send(message, strlen(message), MPI_CHAR, i, 99, MPI_COMM_WORLD);
            
        }
        printf(" \n Continuando ...");
    }
    else
    {
        printf("Proceso %d Esperando...\n", my_rank);
        MPI_Recv(recieved, 20, MPI_CHAR, 0, 99, MPI_COMM_WORLD, &status);
    }
    MPI_Finalize();
}