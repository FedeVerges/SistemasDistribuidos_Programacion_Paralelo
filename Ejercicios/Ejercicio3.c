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

    // for(int i=0; i< rows; i++){
    //     int row
    // }

    // Utilizar broadcast para enviar el vector a los demas procesos.

    // Utilizar Gather para recolectar los resultados del resto de los procesos al proceso 0.

    // Utilizar Scatter para distribuir el vector a los demás procesos.
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

    int indice = 0;
    int vector[6]; // buffer
    int cant_columns = 6;
    int *recvRow = (int *) malloc (sizeof(int)* cant_columns);
    int cant_rows = 6;

    if (world_rank == 0)
    {
        int recvRow[6];
        int vector[6]; // buffer
        int cant_columns = 6;
        int cant_rows = 6;
        int total_values = cant_columns * cant_rows;

        // Generate Data
        int cant_rows_to_send = 5; // The process 0 multiply the first row.
        int columns_send [cant_rows_to_send];

        int matrix[6][6] = {{1, 2, 3, 4, 5, 6}, {7, 8, 9, 10, 11, 12}, {13, 14, 15, 16, 17, 18}, {19, 20, 21, 22, 23, 24}, {25, 26, 27, 28, 29, 30}, {31, 32, 33, 34, 35, 36}};
        
        int values [36] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,25, 26, 27, 28, 29, 30,31, 32, 33, 34, 35, 36};
        
        int array_to_Send [total_values - cant_columns];
        
        int row0 [cant_columns]; // the First row is processed by the process 0.
        
        for (int i=0; i<cant_columns; i+=1){
            vector[i] =i;
            row0[i] = values[i];
        }
        
        for(int i=0; i< total_values - cant_columns; i+=1){
            array_to_Send[i] = values[i + cant_columns];
        }

        MPI_Scatter(array_to_Send, 6, MPI_INT, recvRow, 6, MPI_INT, 0, MPI_COMM_WORLD); // send the colums to each process.
        
        MPI_Bcast(vector,6,MPI_INT,0,MPI_COMM_WORLD);

        int final_result = mulitMatrix(row0, vector, cant_columns);

    }
    else
    {
        for (int i=0; i<cant_columns; i+=1){

           printf("La fila de la matriz es %d \n\n", recvRow[i]);
           printf("El vector enviado es %d \n\n", vector[i]);

        }
    }

    // Finalize the MPI environment. No more MPI calls can be made after this
    MPI_Finalize();
}

int mulitMatrix (int row[], int vector[], int size){
    int result = 0;
    for (int i =0; i<size; i+=1){
        result += row[i] * vector[i];
    }
    return result;
}