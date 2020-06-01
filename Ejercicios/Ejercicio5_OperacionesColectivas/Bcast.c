#include <stdio.h>
#include <string.h>
#include "mpi.h"
int main(int argc, char *argv[])
{
    int my_rank;
    int n;
    MPI_Init(&argc, &argv);
    char message[20], recieved[20];
    strcpy(message,"");
    MPI_Status status;

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    if (my_rank == 0)
    {
        strcpy(message, "hola");
        for (int i = 0; i < world_size ; i+=1)
        {
            MPI_Send(message, strlen(message), MPI_CHAR, i, 99, MPI_COMM_WORLD);
        }
        
    }else{
        MPI_Recv(recieved, 20, MPI_CHAR, 0, 99, MPI_COMM_WORLD, &status);
        printf("%s", recieved);

    }
    MPI_Finalize();
}