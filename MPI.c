#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Utilizzo: %s <dimensione>\n", argv[0]);
        return 1;
    }
    int dim = atoi(argv[1]);
    int dim_res = dim / 2;
    if (dim <= 0)
    {
        printf("La dimensione deve essere un numero intero positivo.\n");
        return 1;
    }

    int len_m = (dim_res + 2) * (dim_res + 2);
    int len_r = dim_res * dim_res;
    float *m = malloc(len_m * sizeof(float));
    float *r = malloc(len_r * sizeof(float));

    if (MPI_Init(&argc, &argv) != MPI_SUCCESS)
    {
        printf("Errore in MPI_Init\n");
        return 1;
    }

    double start = MPI_Wtime();

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (dim_res % size)
    {
        printf("Errore numero di processi non idoneo.\n");
        return 1;
    }
    float *input;
    float *output;
    int *send_recv_counts;
    int *displs;

    input = malloc(3 * dim_res * sizeof(float));
    output = malloc(dim_res * sizeof(float));
    send_recv_counts = (int *)malloc(size * sizeof(int));
    displs = (int *)malloc(size * sizeof(int));

    if (rank == 0)
    {
        for (int i = 0; i < len_m; i++)
        {
            if (i < dim_res + 2 || !(i % (dim_res + 2)))
                m[i] = 0.0;
            else
                m[i] = (float)rand() / RAND_MAX;
        }
    }

    for (int k = 0; k < size; k++)
    {
        send_recv_counts[k] = (dim_res+2) * 3;
        displs[k] = (dim_res +2) * k;
    }

    if (MPI_Scatterv(m, send_recv_counts, displs, MPI_FLOAT, input, send_recv_counts, MPI_FLOAT, 0, MPI_COMM_WORLD) != MPI_SUCCESS)
    {
        printf("Errore in MPI_Scatter\n");
        return 1;
    }

    float sum = 0.0;
    sum = input[1]+input[2]+
                input[(dim_res+2)+1] + input[(dim_res+2)+2] +
                input[2*(dim_res+2)+1] + input[2*(dim_res+2)+2];
    output[0] = sum / 9.0;
    for (int j = 2; j < dim_res + 1; j++)
    {
        for (int k = 0; k <= 2; k++)
            sum += input[(dim_res +2)* k + j + 1] - input[(dim_res +2) * k + j - 2];
        output[j - 1] = sum / 9.0;
    }

    if (MPI_Gather(output, dim_res, MPI_FLOAT, r, dim_res, MPI_FLOAT, 0, MPI_COMM_WORLD) != MPI_SUCCESS)
    {
        printf("Errore in MPI_Gather\n");
        return 1;
    }

    if (rank == 0)
    {
        for (int i = 0; i < len_r; i++)
        {
            if (!(i % dim_res))
                printf("\n");
            printf("%f\t", r[i]);
        }
        printf("\n");
    }

    if (MPI_Barrier(MPI_COMM_WORLD) != MPI_SUCCESS)
    {
        printf("Errore in MPI_Barrier\n");
        return 1;
    }

    free(send_recv_counts);
    free(displs);
    free(input);
    free(output);

    if (rank == 0)
    {
        double end = MPI_Wtime();
        printf("Dimensione Matrice: %d\nNumero Processi: %d\nTempo Impiegato: %f\n", dim, size, end - start);

        free(m);
        free(r);
    }

    if (MPI_Finalize() != MPI_SUCCESS)
    {
        printf("Errore in MPI_Finalize\n");
        return 1;
    }
    return 0;
}
