#include <stdlib.h>
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
// Initialize the MPI environment. The two arguments to MPI Init are not
// currently used by MPI implementations, but are there in case future
// implementations might need the arguments.
MPI_Init(NULL, NULL);
char message[50],recieved[50];
MPI_Status status;

// Get the number of processes
int world_size;
MPI_Comm_size(MPI_COMM_WORLD, &world_size);

// Get the rank of the process
int world_rank;
MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

// Get the name of the processor
char processor_name[MPI_MAX_PROCESSOR_NAME];
int name_len;
MPI_Get_processor_name(processor_name, &name_len);
    strcpy(message, "hola soy el proceso 1 ");
    MPI_Send(message, strlen(message),MPI_CHAR,0,99,MPI_COMM_WORLD);
    if(world_rank == 0){
         // Codigo del proceso 0
        MPI_Recv(recieved,50,MPI_CHAR,1,99, MPI_COMM_WORLD, &status);
        printf("Hola soy el proceso 0 y recibo %s\n\n", recieved);

    }
// Print off a hello world message
printf("Hello world from processor %s, rank %d out of %d processors\n",
processor_name, world_rank, world_size);

// Finalize the MPI environment. No more MPI calls can be made after this
MPI_Finalize();
}