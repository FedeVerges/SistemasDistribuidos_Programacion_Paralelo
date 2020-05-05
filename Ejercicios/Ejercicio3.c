#include <stdlib.h>
#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    int cant_columns = 6;
    int cant_rows = 12;
    int total_values =  cant_columns * cant_rows;
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

    if (world_rank == 0)
    {
        for (int i = 0; i < total_values; i += 1)
        { // Generate values.
            matrix[i] = i + 1;
        }
        for (int i = 0; i < cant_columns; i += 1)
        { // generate Vector
            vector[i] = i + 1;
        }
    }

    

    MPI_Scatter(matrix, cant_columns, MPI_INT, recvRow, cant_columns, MPI_INT, 0, MPI_COMM_WORLD); // divide de rows of the matrix.
    
    MPI_Bcast(&vector, cant_columns, MPI_INT, 0, MPI_COMM_WORLD);                       // Share the vector to each process.

    int final_result = mulitMatrix(recvRow, vector, cant_columns);
    int result_vector[cant_columns];

    MPI_Gather(&final_result, 1, MPI_INT, result_vector, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank == 0)
    {
        printf("el resultado de la operacion es ( ");
        for (int i = 0; i < cant_rows; i += 1)
        {
            printf(" %d ", result_vector[i]);
        }
        printf(" ). ");
    }
    // Finalize the MPI environment. No more MPI calls can be made after this
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

void freeData()
{
}