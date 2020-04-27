#include <stdlib.h>
#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{

    // Message
    char message[20];
    char recieved[20];
    // Initialize the MPI environment. The two arguments to MPI Init are not
    // currently used by MPI implementations, but are there in case future
    // implementations might need the arguments.

    MPI_Status status;
    MPI_Init(NULL, NULL);

    //Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
    if (world_rank == 0)
    {
        strcpy(message, "Hola, soy el proceso 0");
        MPI_Send(message, strlen(message), MPI_CHAR, world_rank++, 99, MPI_COMM_WORLD);
        MPI_Recv(recieved, 20, MPI_CHAR, world_size--, 99, MPI_COMM_WORLD, &status);
        printf("Recibido el mensaje: %s\n", recieved);
    }
    else if (world_rank == world_size--)
    {
        MPI_Recv(recieved, 20, MPI_CHAR, world_rank--, 99, MPI_COMM_WORLD, &status);
        MPI_Send(recieved, strlen(recieved), MPI_CHAR, 0, 99, MPI_COMM_WORLD);
        printf("Recibido el mensaje: %s\n", recieved);
    }
    else
    {
        MPI_Recv(recieved, 20, MPI_CHAR, world_rank--, 99, MPI_COMM_WORLD, &status);
        MPI_Send(recieved, strlen(recieved), MPI_CHAR, world_rank++, 99, MPI_COMM_WORLD);
    }

    // Finalize the MPI environment. No more MPI calls can be made after this
    MPI_Finalize();
}
