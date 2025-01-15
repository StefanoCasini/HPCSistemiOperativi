#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
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
    float m[len_m];
    float r[len_r];

    if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
        printf("Errore in MPI_Init\n");
        return 1;
    }
    
    double start = MPI_Wtime();

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (dim_res % size) {
    	printf("Errore numero di processi non idoneo.\n");
        return 1;
    }

    float input[3 * dim_res];
    float output[dim_res];
    
	if (rank == 0) for (int i = 0; i < len_m; i++) {
		if (i < dim_res + 2 || !(i % (dim_res + 2))) m[i] = 0.0;
		else m[i] = (float) rand() / RAND_MAX;
	}
	
	int send_recv_counts[size], displs[size];
	for (int k = 0; k < size; k++) {
		send_recv_counts[k] = dim_res * 3; 
		displs[k] = dim_res * k ;
	}

	if (MPI_Scatterv(m, send_recv_counts, displs, MPI_FLOAT, &input, send_recv_counts, MPI_FLOAT, 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
        printf("Errore in MPI_Scatter\n");
        return 1;
    }
    
    float sum = 0.0;
    output[0] = (input[0] + input[1] + input[dim_res] + input[dim_res + 1] +
    					input[2 * dim_res] + input[2 * dim_res + 1]) / 9.0;
    for (int j = 2; j < dim_res + 1; j++) {
    	for (int k = -1; k <= 1; k++) sum += input[dim_res * k + j + 1] - input[dim_res * k + j - 2];
    	output[j - 1] = sum / 9.0;
    }
    
    if (MPI_Gather(&output, dim_res, MPI_FLOAT, r, dim_res, MPI_FLOAT, 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
        printf("Errore in MPI_Gather\n");
        return 1;
    }

    if (rank == 0) for (int i = 0; i < len_r; i++) {
        printf("%f\t", r[i]);
        if (!(i % dim_res)) printf("\n");
    }
    
    if (MPI_Barrier(MPI_COMM_WORLD) != MPI_SUCCESS) {
        printf("Errore in MPI_Barrier\n");
        return 1;
    }
    
    double end = MPI_Wtime();
    printf("Dimensione Matrice: %d\nNumero Processi: %d\nTempo Impiegato: %f\n", dim, size, end - start);

    if (MPI_Finalize() != MPI_SUCCESS) {
        printf("Errore in MPI_Finalize\n");
        return 1;
    }
    return 0;
}
