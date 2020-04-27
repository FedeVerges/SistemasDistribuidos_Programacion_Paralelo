#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
// Ejercicio 1.b pero con los mensajes ordenados.
int main(int argc, char **argv)
{
  // Initialize the MPI environment. The two arguments to MPI Init are not
  // currently used by MPI implementations, but are there in case future
  // implementations might need the arguments.
  MPI_Init(NULL, NULL);
  char message[50], recieved[50];
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

  if (world_rank == 0)
  { // Proceso que imprimirá los resultados.
    // Codigo del proceso 0
    int indice = 1;
    for (indice; indice < world_size; indice++)
    {
      MPI_Recv(recieved, 50, MPI_CHAR, MPI_ANY_SOURCE, 99, MPI_COMM_WORLD, &status);
      printf("Hola soy el proceso 0 y recibo un mensaje del proceso %s\n\n", recieved);
    }
  }
  else
  {
    char numero_proceso[20];                   // Entero pasado a String.
    sprintf(numero_proceso, "%i", world_rank); // Convierto el numero del proceso a string para poder mandarlo por el mensaje
    strcpy(message, numero_proceso);
    MPI_Send(message, strlen(message), MPI_CHAR, 0, 99, MPI_COMM_WORLD);
  }

  // Finalize the MPI environment. No more MPI calls can be made after this
  MPI_Finalize();
}
