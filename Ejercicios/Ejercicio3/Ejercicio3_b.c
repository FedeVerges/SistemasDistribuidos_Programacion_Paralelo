#include <stdlib.h>
#include <mpi.h>
#include <stdio.h>
#include <string.h>

void getSubMatrix(int matrix[], int submatrix[], int start, int finish)
{
    // get the matri'x part to send.
    for (int i = start; i < finish; i += 1)
    {
        submatrix[i - start] = matrix[i];
    }
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


int main(int argc, char **argv)
{
    int cant_columns = 5; // cant_columns = row lenght
    int cant_rows = 5;
    int total_values = cant_columns * cant_rows;

    int no_repeat = 0;   // To Print correctly the vector.
    int indexUnique = 0; // Index for print once the result vector

    int result_vector[cant_columns]; // Result Vector.

    if (argc != 2)
    {
        printf("Cantidad de argumentos erronea");
        exit(1);
    }

    // Initialize the MPI environment. The two arguments to MPI Init are not
    // currently used by MPI implementations, but are there in case future
    // implementations might need the arguments.
    MPI_Init(&argc, &argv);
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

    int recvRow[cant_columns]; // Shared array to send the values of matri'x columns.
    int matrix[total_values];  // Matrix
    int vector[cant_columns];  // Vector

    if (world_rank == 0)
    {

        for (int i = 0; i < total_values; i += 1)
        {
            // Generate values.
            // Generando el vector con las filas de la matriz
            matrix[i] = i + 1;
        }
        for (int i = 0; i < cant_columns; i += 1)
        {
            // Generate Vector
            vector[i] = i + 1;
        }
    }

    int cant_elements_to_send = cant_columns * world_size; // amount elements to send on Scatter.
    int submatrix[cant_elements_to_send];                  // Array to keep the part of the matrix to send on Scatter.

    int result; // Final result of the multiplication.

    MPI_Bcast(&vector, cant_columns, MPI_INT, 0, MPI_COMM_WORLD); // Share the vector to each process.

    for (int i = 0; i < total_values; i += cant_elements_to_send)
    {
        getSubMatrix(matrix, submatrix, i, i + cant_elements_to_send);

        MPI_Scatter(submatrix, cant_columns, MPI_INT, recvRow, cant_columns, MPI_INT, 0, MPI_COMM_WORLD); // share the rows of the matrix.

        result = mulitMatrix(recvRow, vector, cant_columns); 

        MPI_Gather(&result, 1, MPI_INT, result_vector, 1, MPI_INT, 0, MPI_COMM_WORLD); //  The Process 0 collect the data from the other process.


        // Printing Values.
        if (world_rank == 0)
        {
            if (no_repeat == 0)
            {
                printf("Vector Resultado : ");
            }
            for (int i = 0; i < world_size; i += 1)
            {
                if (indexUnique < cant_columns)
                {
                    printf(" %d ", result_vector[i]);
                }
                indexUnique++;
            }

            no_repeat += 1;
        }
        result = 0;
    }

    MPI_Finalize();
}
