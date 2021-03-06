#include <stdlib.h>
#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    // Initialize the MPI environment. The two arguments to MPI Init are not
    // currently used by MPI implementations, but are there in case future
    // implementations might need the arguments.
    MPI_Init(NULL, NULL);
    MPI_Status status;
    // Message
    char message[50];
    char recieved[50];

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


    int partner_Process = (world_rank+1) % world_size;
    int laps = 5;
    int indice=0;
    for(indice; indice<laps; indice+1){
        
        if (world_rank == 0)
        {
            printf("lap %d \n\n", indice);
            strcpy(message, "Hola, soy el proceso 0");
            MPI_Send(message, strlen(message), MPI_CHAR, partner_Process, 99, MPI_COMM_WORLD);
            printf("Mensaje del proceso 0 enviado \n\n");
            MPI_Recv(recieved, 50, MPI_CHAR, world_size-1, 99, MPI_COMM_WORLD, &status);
            printf("Recibido el mensaje: %s\n", recieved);
        }
        else
        {
            MPI_Recv(recieved, 50, MPI_CHAR, world_rank-1, 99, MPI_COMM_WORLD, &status);
            MPI_Send(recieved, strlen(recieved), MPI_CHAR, partner_Process, 99, MPI_COMM_WORLD);
            printf("process %d send message to process %d \n", world_rank, partner_Process);
        }
    
    }

    // Finalize the MPI environment. No more MPI calls can be made after this
    MPI_Finalize();
}
