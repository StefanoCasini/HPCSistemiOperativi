#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float **create_matrix(int dim)
{
    float **matrice = malloc(dim * sizeof(float *));
    for (int i = 0; i < dim; i++)
        matrice[i] = malloc(dim * sizeof(float));
    for (int i = 0; i < dim; i++)
        matrice[i][0] = matrice[0][i] = 0.0;
    for (int i = 1; i < dim; i++)
        for (int j = 1; j < dim; j++)
            matrice[i][j] = (float)rand() / RAND_MAX;
    return matrice;
}

void free_matrix(float **m, int dim)
{
    for (int i = 0; i < dim; i++)
        free(m[i]);
    free(m);
}

void show_matrix(float **m, int dim)
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            float val = m[i][j];
            printf("%f\t", val);
        }
        printf("\n");
    }
    printf("\n");
}

float first_sum_adj(float **m, int i, int j)
{
    float sum = 0;
    for (int ik = -1; ik < 2; ik++)
        for (int jk = -1; jk < 2; jk++)
            sum += m[i + ik][j + jk];
    return sum;
}

float shift_sum_adj(float **m, float old_sum, int i_from, int j_from, int i_to, int j_to)
{
    float sum = old_sum;
    int dir = j_to - j_from;
    if (dir)
    {
        for (int k = -1; k < 2; k++)
            sum -= m[i_from + k][j_from - 1 * dir];
        for (int k = -1; k < 2; k++)
            sum += m[i_to + k][j_to + 1 * dir];
    }
    else
    {
        for (int k = -1; k < 2; k++)
            sum -= m[i_from - 1][j_from + k];
        for (int k = -1; k < 2; k++)
            sum += m[i_to + 1][j_to + k];
    }
    return sum;
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Utilizzo: %s <dimensione>\n", argv[0]);
        return 1;
    }

    int dim = atoi(argv[1]);
    int dim_res = dim / 2;
    int dim_frm = dim_res + 2;

    int size = atoi(argv[2]);
    printf("SIZE: %d\n", size);

    if (dim <= 0)
    {
        printf("La dimensione deve essere un numero intero positivo.\n");
        return 1;
    }

    double start = omp_get_wtime();

    float **m = create_matrix(dim_frm);
    float **r = create_matrix(dim_res);

    int cols = size > dim_res ? dim_res : sqrt(size);
    int dim_col = dim_res / cols;
    int big_cols = dim_res % cols;
    // int rows = size / cols > dim_res ? dim_res : size / cols;
    // int dim_row = dim_res / rows;
    // int big_rows = dim_res % rows;

    int threadsInCol = size / cols;
    int big_threadsInCol = size % cols;

    printf("cols: %d\n", cols);
    printf("dim_col: %d\n", dim_col);
    printf("big_cols: %d\n", big_cols);
    printf("threadsInCol: %d\n", threadsInCol);
    // printf("dim_row: %d\n", dim_row);
    printf("big_threadsInCol: %d\n", big_threadsInCol);

    omp_set_nested(1);
#pragma omp parallel num_threads(cols) shared(m, r, dim_col, big_cols, big_threadsInCol, threadsInCol, dim_res)
    {
        int rank = omp_get_thread_num();
        int subthreads = (rank < big_threadsInCol && big_threadsInCol != 0) ? threadsInCol + 1 : threadsInCol;

        int shift = rank * (dim_col);
        if (rank >= big_cols && big_cols != 0)
            shift += (rank - big_cols) * dim_col;
        int j_from = 1 + shift;
        int j_to = (rank > big_cols && big_cols != 0 ? 1 : 0) + dim_col + shift;
        printf("[RANK %d] : Subthreads %d\n", rank, subthreads);
// Nested pragma
#pragma omp parallel num_threads(subthreads) shared(j_from, j_to, m, r, big_threadsInCol, dim_res) firstprivate(subthreads)
        {
            int nst_rank = omp_get_thread_num();
            // int nst_shift = nst_rank * (big_threadsInCol + 1);
            // if (nst_rank >= big_threadsInCol && big_threadsInCol!=0)
            //     nst_shift += (nst_rank - big_threadsInCol) * subthreads;
            // int i_from = 1 + nst_shift;
            // int i_to = (nst_rank >= big_threadsInCol && big_cols != 0 ? 1 : 0) + subthreads + nst_shift;

            int dim_rows = dim_res / subthreads;
            int big_rows = dim_res % subthreads;
            int nst_shift = nst_rank * (dim_rows);
            if (nst_rank < big_rows && big_rows != 0)
                nst_shift += (rank - big_rows) * dim_rows;
            int i_from = 1 + nst_shift;
            int i_to = (nst_rank > big_rows && big_rows != 0 ? 1 : 0) + dim_rows + nst_shift;

            printf("[RANK %d]: %d, %d, %d, %d\n", rank, j_from, j_to, i_from, i_to);

            float sum = 0.0;
            for (int i = i_from; i <= i_to; i++)
            {
                if (((i - i_from) % 2) == 0)
                {
                    for (int j = j_from; j <= j_to; j++)
                    {
                        if (i == i_from && j == j_from)
                            sum = first_sum_adj(m, i_from, j_from);
                        else if (j == j_from)
                            sum = shift_sum_adj(m, sum, i - 1, j, i, j);
                        else
                            sum = shift_sum_adj(m, sum, i, j - 1, i, j);
                        r[i - 1][j - 1] = sum / 9.0;
                    }
                }
                else
                    for (int j = j_to; j >= j_from; j--)
                    {
                        if (j == j_to)
                            sum = shift_sum_adj(m, sum, i - 1, j, i, j);
                        else
                            sum = shift_sum_adj(m, sum, i, j + 1, i, j);
                        r[i - 1][j - 1] = sum / 9.0;
                    }
            }
        }
    }

    show_matrix(m, dim_frm);
    show_matrix(r, dim_res);
    free_matrix(m, dim_frm);
    free_matrix(r, dim_res);

    double end = omp_get_wtime();
    printf("Dimensione Matrice: %d\nNumero Processi: %d\nTempo Impiegato: %f\n", dim, size, end - start);

    return 0;
}