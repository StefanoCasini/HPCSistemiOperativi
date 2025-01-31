#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Utilizzo: %s <dimensione>\n", argv[0]);
        return 1;
    }
    int dim = atoi(argv[1]);
    int dim_res = dim / 2;
    if (dim <= 0) {
        printf("La dimensione deve essere un numero intero positivo.\n");
        return 1;
    }
    int len_m = (dim_res + 2) * (dim_res + 2);
    int len_r = dim_res * dim_res;
    float *m = malloc(len_m * sizeof(float));
    float *r = malloc(len_r * sizeof(float));
    if (m == NULL || r == NULL) {
		printf("Errore nell'allocazione di memoria.\n");
		return 1;
	}
    if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
        printf("Errore in MPI_Init\n");
        return 1;
    }
    double start = MPI_Wtime();
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int *send_counts = (int *)malloc(size * sizeof(int));
    int *recv_counts = (int *)malloc(size * sizeof(int));
    int *send_displs = (int *)malloc(size * sizeof(int));
    int *recv_displs = (int *)malloc(size * sizeof(int));
    if (send_counts == NULL || recv_counts == NULL || send_displs == NULL || recv_displs == NULL) {
		printf("Errore nell'allocazione di memoria.\n");
		return 1;
	}
    if (rank == 0) for (int i = 0; i < len_m; i++) {
		if (i < dim_res + 2 || !(i % (dim_res + 2))) m[i] = 0.0;
        else m[i] = (float)rand() / RAND_MAX;
    }
    int base_rows = dim_res / size;
	int extra_rows = dim_res % size;
	int max_rows = extra_rows ? base_rows + 1 : base_rows;
	float *input = malloc((max_rows + 2) * dim_res * sizeof(float));
    float *output = malloc(max_rows * dim_res * sizeof(float));
	int rows = base_rows + 1;
	bool extra = true;
	for (int k = 0, send_offset = 0, recv_offset = 0; k < size; k++) {
		if (extra && k == extra_rows) {
		    rows--;
		    extra = false; 
		}
		send_counts[k] = (rows + 2) * (dim_res + 2);
		recv_counts[k] = rows * dim_res;
		send_displs[k] = send_offset;
		send_offset += rows * (dim_res + 2);
		recv_displs[k] = recv_offset;
		recv_offset += rows * dim_res;
	}

	/*if (MPI_Scatterv(m, send_recv_counts, displs, MPI_FLOAT, input, send_recv_counts, MPI_FLOAT, 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
        printf("Errore in MPI_Scatter\n");
        return 1;
    }*/
    if (MPI_Scatterv(m, send_counts, send_displs, MPI_FLOAT, input, recv_counts[rank], MPI_FLOAT, 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
		printf("Errore in MPI_Scatterv\n");
		return 1;
	}	
	
    /*float sum = input[1] + input[2] +
    		input[(dim_res + 2) + 1] + input[(dim_res + 2) + 2] +
    		input[2 * (dim_res + 2) + 1] + input[2 * (dim_res + 2) + 2];
    output[0] = sum / 9.0;
    for (int j = 2; j < dim_res + 1; j++) {
        for (int k = 0; k <= 2; k++) sum += input[(dim_res + 2)* k + j + 1] - input[(dim_res + 2) * k + j - 2];
        output[j - 1] = sum / 9.0;
    }*/
    int input_rows = send_counts[rank] / (dim_res + 2);
    for (int i = 0; i < input_rows - 1; i++) {
    	float sum = input[i * (dim_res + 2) + 1] + input[i * (dim_res + 2) + 2] +
    				input[(i + 1) * (dim_res + 2) + 1] + input[(i + 1) * (dim_res + 2) + 2] +
    				input[(i + 2) * (dim_res + 2) + 1] + input[(i + 2) * (dim_res + 2) + 2];
		output[0] = sum / 9.0;
		int first_line = i * (dim_res + 2);
		for (int j = 2; j < dim_res + 1; j++) {
		    for (int k = 0; k <= 2; k++) {
		    	int center = first_line + k * (dim_res + 2);
		    	sum += input[center + j + 1] - input[center + j - 2];
		    }
		    output[i * dim_res + j - 1] = sum / 9.0;
		}
    }
    
    /*if (MPI_Gather(output, dim_res, MPI_FLOAT, r, dim_res, MPI_FLOAT, 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
        printf("Errore in MPI_Gather\n");
        return 1;
    }*/
    if (MPI_Gatherv(output, send_counts[rank], MPI_FLOAT, r, recv_counts, recv_displs, MPI_FLOAT, 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
		printf("Errore in MPI_Gatherv\n");
		return 1;
	}
    
    /*if (rank == 0) {
    	for (int i = 0; i < len_r; i++) {
		    if (!(i % dim_res)) printf("\n");
		    printf("%f\t", r[i]);
        }
        printf("\n");
    }*/
    /*if (MPI_Barrier(MPI_COMM_WORLD) != MPI_SUCCESS) {
        printf("Errore in MPI_Barrier\n");
        return 1;
    }*/
    free(send_counts);
    free(recv_counts);
    free(send_displs);
    free(recv_displs);
    free(input);
    free(output);
    if (rank == 0) {
        double end = MPI_Wtime();
        printf("Dimensione Matrice: %d\nNumero Processi: %d\nTempo Impiegato: %f\n", dim, size, end - start);
        free(m);
        free(r);
    }
    if (MPI_Finalize() != MPI_SUCCESS) {
        printf("Errore in MPI_Finalize\n");
        return 1;
    }
    return 0;
}

// si può usare MPI_Abort(MPI_COMM_WORLD, 1); invece di return 1
