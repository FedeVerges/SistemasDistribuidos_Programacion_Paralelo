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

    int cant_columns = 6;
    int cant_rows = 6;
    int total_values = cant_columns * cant_rows;

    int *recvRow = (int *) malloc (sizeof(int)* cant_columns); // create the buffer.
    int *matrix = (int *) malloc (sizeof(int)* total_values); // create the matriz buffer.
    int *vector  = (int *) malloc (sizeof(int)* cant_columns);
    if (world_rank == 0)
    {
        // // Generate Data
        // int cant_rows_to_send = 5; // The process 0 multiply the first row.
        // int columns_send [cant_rows_to_send];

        //int matrix[6][6] = {{1, 2, 3, 4, 5, 6}, {7, 8, 9, 10, 11, 12}, {13, 14, 15, 16, 17, 18}, {19, 20, 21, 22, 23, 24}, {25, 26, 27, 28, 29, 30}, {31, 32, 33, 34, 35, 36}};
        
        // *(matrix) [36] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,25, 26, 27, 28, 29, 30,31, 32, 33, 34, 35, 36};
        
        // int array_to_Send [total_values - cant_columns];
        
        // int row0 [cant_columns]; // the First row is processed by the process 0.
        
        // for (int i=0; i<cant_columns; i+=1){
        //     vector[i] =i;
        //     row0[i] = values[i];
        // }
        
        for(int i=0; i<total_values; i+=1){ // Generate values.
            matrix[i] = i+1;
        }
        for(int i=0; i< cant_columns; i+=1){ // generate Vector
            vector[i]=i+1;
        }

    }
    MPI_Scatter(matrix, 6, MPI_INT, recvRow, 6, MPI_INT, 0, MPI_COMM_WORLD); // send the colums to each process.
    MPI_Bcast(&vector,6,MPI_INT,0,MPI_COMM_WORLD);

    printf("valor del primer elemento del vector %d \n", vector[0]);
    printf("soy el proceso %d y mi valor de la primer fila  %d \n", world_rank,recvRow[0]);
    
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

void freeData(){
    
}