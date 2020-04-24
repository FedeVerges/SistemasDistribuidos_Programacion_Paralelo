#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

main(int argc, char **argv)
{
    int argc;
    char **argv;

    char message[99];
    int node;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &node);
    if(node ==0){ // Codigo para el proceso 0
        MPI_Recv(message,strlen(message), MPI_CHAR,1,99,MPI_COMM_WORLD, &status);
        printf("Hola, soy el proceso 1 y recibo : %s", &message);
    }else
    {
        strcpy(message,"Saludos desde el proceso %d", node);
        MPI_Send(message,strlen(message), MPI_CHAR,0,99,MPI_COMM_WORLD);
    }
    
}