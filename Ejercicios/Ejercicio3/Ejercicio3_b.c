#include <stdlib.h>
#include <mpi.h>
#include <stdio.h>
#include <string.h>

void getSubMatrix(int matrix[], int submatrix[], int start, int finish)
{
    // Eliminar las filas compartidas de la matriz.
    for (int i = start; i < finish; i += 1)
    {
        submatrix[i - start] = matrix[i];
    }
}

int main(int argc, char **argv)
{
    int cant_columns = 6;
    int cant_rows = 6;
    int total_values = cant_columns * cant_rows;
    // Initialize the MPI environment. The two arguments to MPI Init are not
    // currently used by MPI implementations, but are there in case future
    // implementations might need the arguments.
    MPI_Init(NULL, NULL);
    MPI_Status status;

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

    int recvRow[cant_columns];
    int matrix[total_values];
    int vector[cant_columns];
    int result_vector[cant_columns];


    if (world_rank == 0)
    {
        for (int i = 0; i < total_values; i += 1)
        {                      // Generate values.
            matrix[i] = i + 1; // generando el vector con las filas de la matriz
        }
        for (int i = 0; i < cant_columns; i += 1)
        { // generate Vector
            vector[i] = i + 1;
        }
    }

    // asumir que la info es enviada a todos los procesos

    // otra opcion.
    // En el caso de 6 filas, 3 procesos, 2 filas por proceso.

    if (cant_rows % world_size == 0)
    {                                                          // Caso de filas multiplo de procesos.
        int rows_for_process = cant_rows / world_size;         // cuantas filas le corresponden a cada proceso.
        int cant_elements_to_send = cant_columns * world_size; // cantidad de elementos por tanda a enviar.
        int submatrix[cant_elements_to_send];

        int final_result[rows_for_process]; // vector resultado.
        
        MPI_Bcast(&vector, cant_columns, MPI_INT, 0, MPI_COMM_WORLD); // Share the vector to each process.

        for (int i = 0; i < rows_for_process; i += 1)
        {

            getSubMatrix(matrix, submatrix, (cant_elements_to_send * i), cant_elements_to_send * (i+1)); // dividimos la matriz

            MPI_Scatter(submatrix, cant_columns, MPI_INT, recvRow, cant_columns, MPI_INT, 0, MPI_COMM_WORLD); // compartos las filas para cada proceso.

            final_result[i]=mulitMatrix(recvRow, vector, cant_columns); 
            
            MPI_Gather(&final_result[i], 1, MPI_INT, result_vector, 1, MPI_INT, 0, MPI_COMM_WORLD);
        


        }
    }


    //  // tomar como un arreglo, hacer un for.
    

    // PENSAR EN FORMA DE IR DIVIDIENDO LAS FILAS ENTRE LOS PROCESOS.

    // 
    // Como almaceno lso resultados!!.

    // if (world_rank == 0)
    // {
    //     printf("el resultado de la operacion es ( ");
    //     for (int i = 0; i < cant_rows; i += 1)
    //     {
    //         printf(" %d ", result_vector[i]);
    //     }
    //     printf(" ). ");
    // }
    // // Finalize the MPI environment. No more MPI calls can be made after this
    MPI_Finalize();
}

int mulitMatrix(int row[], int vector[], int size)
{
    int result = 0;
    for (int i = 0; i < size; i += 1)
    {
        result += row[i] * vector[i];
    }
    return result;
}
