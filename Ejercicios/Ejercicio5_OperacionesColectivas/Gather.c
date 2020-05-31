#include <stdio.h>
#include <string.h>
#include "mpi.h"
int main(int argc, char *argv[])
{
    int my_rank;
    MPI_Init(&argc, &argv);
    char message[20], recieved[20];


    strcpy(message, "");
    MPI_Status status;

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0)
    {
        int indice = 1;
        printf("Iniciando Gather ...\n ");

        for (indice; indice < world_size; indice++)
        {
            MPI_Recv(recieved, 50, MPI_CHAR, indice, 99, MPI_COMM_WORLD, &status);
            printf("Mensaje del proceso %d:  %s \n\n", indice, recieved);
            // cargar recieved en un arreglo.
            
        }
    }
    else
    {
        char numero_proceso[20];                // Entero pasado a String.
        sprintf(numero_proceso, "%i", my_rank); // Convierto el numero del proceso a string para poder mandarlo por el mensaje
        strcpy(message, numero_proceso);
        MPI_Send(message, strlen(message), MPI_CHAR, 0, 99, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}