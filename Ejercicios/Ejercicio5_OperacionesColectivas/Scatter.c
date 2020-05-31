#include <stdlib.h>
#include <mpi.h>
#include <stdio.h>
#include <string.h>
#define SIZE_ARRAY 10
int main(int argc, char **argv)
{
    // Initialize the MPI environment. The two arguments to MPI Init are not
    // currently used by MPI implementations, but are there in case future
    // implementations might need the arguments.
    MPI_Init(NULL, NULL);
    MPI_Status status;
    // Message
    int data[SIZE_ARRAY];
    for (int j = 0; j < SIZE_ARRAY; j++)

    {
        data[j] = j;
    }

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

    int element_per_process = SIZE_ARRAY / world_size; // Calculated or modified by the user.
    int messege[SIZE_ARRAY];
    int recieved[SIZE_ARRAY];

    if (world_rank == 0)
    {
        int indice = 1;
        for (indice; indice < world_size; indice += 1)
        {
            for (int i = 0; i < element_per_process; i += 1)
            {
                messege[i] = data[i + (element_per_process * indice)];
            }
            MPI_Send(messege, element_per_process, MPI_INT, indice, 99, MPI_COMM_WORLD);
            
        }
        printf("Elementos Proceso 0:\n");
            for (int i = 0; i < element_per_process; i++)
            {
                printf(" %d", data[i]);
            }
            printf("\n\n ");
    }
    else
    {
        MPI_Recv(recieved, element_per_process, MPI_INT, 0, 99, MPI_COMM_WORLD, &status);
        printf("Elementos Proceso %d:\n", world_rank);
        for (int i = 0; i < element_per_process; i++)
        {
            printf(" %d", recieved[i]);
        }
        printf("\n\n ");
    }

    // Finalize the MPI environment. No more MPI calls can be made after this
    MPI_Finalize();
}
