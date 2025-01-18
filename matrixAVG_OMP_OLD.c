#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float **create_matrix(int dim) {
    float **matrice = malloc(dim * sizeof(float *));
    for (int i = 0; i < dim; i++) matrice[i] = malloc(dim * sizeof(float));
    for (int i = 0; i < dim; i++) matrice[i][0] = matrice[0][i] = 0.0;
    for (int i = 1; i < dim; i++) for (int j = 1; j < dim; j++) matrice[i][j] = (float) rand() / RAND_MAX;
    return matrice;
}

void free_matrix(float **m, int dim) {
    for (int i = 0; i < dim; i++) free(m[i]);
    free(m);
}

void show_matrix(float **m, int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) printf("%f\t", m[i][j]);
        printf("\n");
    }
    printf("\n");
}

float first_sum_adj(float **m, int i, int j) {
	float sum = 0;
	for (int ik = -1; ik < 2; ik++) for (int jk = -1; jk < 2; jk++) sum += m[i + ik][j + jk];
	return sum;
}

float shift_sum_adj(float **m, float old_sum, int i_from, int j_from, int i_to, int j_to) {
    float sum = old_sum;
    int dir = j_to - j_from;
    if (dir) {
    	for (int k = -1; k < 2; k++) sum -= m[i_from + k][j_from - 1 * dir];
    	for (int k = -1; k < 2; k++) sum += m[i_to + k][j_to + 1 * dir];
    } else {
    	for (int k = -1; k < 2; k++) sum -= m[i_from - 1][j_from + k];
    	for (int k = -1; k < 2; k++) sum += m[i_to + 1][j_to + k];
    }
    return sum;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Utilizzo: %s <dimensione>\n", argv[0]);
        return 1;
    }
    int dim = atoi(argv[1]);
    int dim_res = dim / 2;
    int dim_frm = dim_res + 2;
    if (dim <= 0) {
        printf("La dimensione deve essere un numero intero positivo.\n");
        return 1;
    }
    
    double start = omp_get_time();

    float **m = create_matrix(dim_frm);
    float **r = create_matrix(dim_res);
    int size = omp_get_num_threads();
    
	int cols = size > dim_res ? dim_res : sqrt(size);
	int dim_col = dim_res / cols;
	int big_cols = dim_res % cols;
	int rows = size / cols > dim_res ? dim_res : size / cols;
	int dim_row = dim_res / rows;
	int big_rows = dim_res % rows;
	
	omp_set_nested(1);
    
    #pragma omp parallel num_threads(cols) shared(m, r) {
		int rank = omp_get_thread_num();
    	int shift = rank * (dim_col + 1);
    	if (rank > big_cols) shift += (rank - big_cols) * dim_col;
    	int j_from = 1 + shift;
    	int j_to = (big_cols > rank ? 0 : 1) + dim_col + shift;
		#pragma omp parallel num_threads(rows) shared(j_from, j_to, m, r) {
			int rank = omp_get_thread_num();
    		int shift = rank * (dim_row + 1);
    		if (rank > big_rows) shift += (rank - big_rows) * dim_row;
    		int i_from = 1 + shift;
    		int i_to = (big_rows > rank ? 0 : 1) + dim_row + shift;
		
			float sum = 0.0;
			for (int i = i_from - 1; i <= i_to + 1; i++) {
				if (i % 2) for (int j = j_from - 1; j <= j_to + 1; j++) {
					if (i == 1 && j == 1) sum = first_sum_adj(m, i, j);
					else if (j == 1) sum = shift_sum_adj(m, sum, i - 1, j, i, j);
					else sum = shift_sum_adj(m, sum, i, j - 1, i, j);
					r[i - i_from + 1][j - j_from + 1] = sum / 9.0;
				} else for (int j = j_to - 1; j <= j_from + 1; j++) {
					if (j == cols - 2) sum = shift_sum_adj(m, sum, i - 1, j, i, j);
					else sum = shift_sum_adj(m, sum, i, j + 1, i, j);
					r[i - i_from + 1][j - j_from + 1] = sum / 9.0;
				}
			}
		}
    }
    
    show_matrix(r, dim_res);
    free_matrix(m, dim_frm);
    free_matrix(r, dim_res);
    
    double end = omp_get_time();
    printf("Dimensione Matrice: %d\nNumero Processi: %d\nTempo Impiegato: %f\n", dim, size, end - start);

    return 0;
}
