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
    int recvRow[6];
    int indice = 0;
    int vector[6]; // buffer
    int cant_columns = 6;
    int cant_rows = 6;

    if (world_rank == 0)
    {
        // Generate Data
        
        int cant_rows_to_send = 5; // The process 0 multiply the first row.
        int columns_send [cant_rows_to_send];

        int matrix[6][6] = {{1, 2, 3, 4, 5, 6}, {7, 8, 9, 10, 11, 12}, {13, 14, 15, 16, 17, 18}, {19, 20, 21, 22, 23, 24}, {25, 26, 27, 28, 29, 30}, {31, 32, 33, 34, 35, 36}};
        int row0 [cant_columns];
        
        for (int i=0; i<cant_columns; i+1){
            vector[i] =i;
            row0[i] = matrix[0][i];    
        }

        for (int i=0; i<cant_columns; i+1){

           printf("La fila del proceso 0 es %d \n\n", row0[i]);
           printf("El vector enviado es %d \n\n", vector[i]);

        }
       
        for(int i=0; i<cant_columns; i+1){ // number of columns.

            for(int f=0; f<cant_rows_to_send; f+1){ // number of rows
                columns_send[f]= matrix[f+1][i];
                
            }

            MPI_Scatter(columns_send, 5, MPI_INT, recvRow[i], 5, MPI_INT, 0, MPI_COMM_WORLD); // send the colums to each process.

        }
        MPI_Bcast(vector,6,MPI_INT,0,MPI_COMM_WORLD);
        int final_result = mulitMatrix(row0, vector);

    }
    else
    {
        for (int i=0; i<cant_columns; i+1){

           printf("La fila de la matriz es %d \n\n", recvRow[i]);
           printf("El vector enviado es %d \n\n", vector[i]);

        }
    }

    // Finalize the MPI environment. No more MPI calls can be made after this
    MPI_Finalize();
}

int mulitMatrix (int row[], int vector[]){
    int cant = strlen(row);
    int result;
    for (int i =0; i<cant; i+1){
        result += row[i] * vector[i];
    }
    return result;
}
