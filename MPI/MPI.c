#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void free_all(float *m, float *r, int *send_counts, int *send_displs, int *recv_counts, int *recv_displs, float *input, float *output, int rank, bool all_malloc) {
    if (!rank) {
        free(m);
        free(r);
    }
    if (all_malloc) {
		free(send_counts);
        free(send_displs);
        free(recv_counts);
        free(recv_displs);
		free(input);
    	free(output);
    }
}

int main(int argc, char **argv) {
	if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
        printf("Errore in MPI_Init\n");
        return 1; //MPI_Abort(MPI_COMM_WORLD, 1);
    }
    if (argc != 2){
        printf("Utilizzo: %s <dimensione>\n", argv[0]);
        return 1;
    }
    int dim = atoi(argv[1]);
    int dim_res = dim / 2;
	int len_r, len_m;
    if (dim <= 1) {
        printf("La dimensione deve essere un numero intero maggiore di 1\n");
        return 1;
    }

    int rank, size;
	double start = 0, end = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    float *m = NULL, *r = NULL, *input = NULL, *output = NULL;
	int *send_counts = NULL, *send_displs = NULL, *recv_counts = NULL, *recv_displs = NULL;
	//MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
    	//start = MPI_Wtime();
		len_m = (dim_res + 2) * (dim_res + 2);
		len_r = dim_res * dim_res;
		m = (float *)malloc(len_m * sizeof(float));
		r = (float *)malloc(len_r * sizeof(float));
		if (m == NULL || r == NULL) {
			printf("Errore nell'allocazione di memoria del processo %d\n", rank);
			free_all(m, r, send_counts, send_displs, recv_counts, recv_displs, input, output, rank, false);
			return 1; //MPI_Abort(MPI_COMM_WORLD, 1);
		}
    	for (int i = 0; i < len_m; i++) {
			if (i < dim_res + 2 || !(i % (dim_res + 2))) m[i] = 0.0;
		    else m[i] = (float)rand() / RAND_MAX;
		}
    }

	MPI_Barrier(MPI_COMM_WORLD);
	if (rank == 0) start = MPI_Wtime();

	send_counts = (int *)malloc(size * sizeof(int));
	send_displs = (int *)malloc(size * sizeof(int));
	recv_counts = (int *)malloc(size * sizeof(int));
	recv_displs = (int *)malloc(size * sizeof(int));

    int base_rows = dim_res / size;
	int extra_rows = dim_res % size;
	int max_rows = extra_rows!=0 ? base_rows + 1 : base_rows;
    input = malloc((max_rows + 2) * (dim_res + 2) * sizeof(float));
    output = malloc(max_rows * dim_res * sizeof(float));
    if (send_counts == NULL || send_displs == NULL || recv_counts == NULL || recv_displs == NULL || input == NULL || output == NULL) {
		printf("Errore nell'allocazione di memoria\n");
		free_all(m, r, send_counts, send_displs, recv_counts, recv_displs, input, output, rank, true);
		return 1; //MPI_Abort(MPI_COMM_WORLD, 1);
	}

	int rows = base_rows + 1;
	bool extra = true;
	for (int k = 0, send_offset = 0, recv_offset = 0; k < size; k++) {
		if (extra && k == extra_rows) {
			rows--;
			extra = false; 
		}
		send_counts[k] = (rows + 2) * (dim_res + 2);
		send_displs[k] = send_offset;
		send_offset += rows * (dim_res + 2);
		recv_counts[k] = rows * dim_res;
		recv_displs[k] = recv_offset;
		recv_offset += rows * dim_res;
	}
    if (MPI_Scatterv(m, send_counts, send_displs, MPI_FLOAT, input, send_counts[rank], MPI_FLOAT, 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
		printf("Errore in MPI_Scatterv\n");
		free_all(m, r, send_counts, send_displs, recv_counts, recv_displs, input, output, rank, true);
		return 1; //MPI_Abort(MPI_COMM_WORLD, 1);
	}

    int input_rows = send_counts[rank] / (dim_res + 2);
    for (int i = 0; i < input_rows - 2; i++) {
    	float sum = input[i * (dim_res + 2) + 1] + input[i * (dim_res + 2) + 2] +
    				input[(i + 1) * (dim_res + 2) + 1] + input[(i + 1) * (dim_res + 2) + 2] +
    				input[(i + 2) * (dim_res + 2) + 1] + input[(i + 2) * (dim_res + 2) + 2];
		output[i * dim_res] = sum / 9.0;
		int first_line = i * (dim_res + 2);
		for (int j = 2; j < dim_res + 1; j++) {
		    for (int k = 0; k <= 2; k++) {
		    	int center = first_line + k * (dim_res + 2);
		    	sum += input[center + j + 1] - input[center + j - 2];
		    }
		    output[i * dim_res + j - 1] = sum / 9.0;			
		}
    }

    if (MPI_Gatherv(output, recv_counts[rank], MPI_FLOAT, r, recv_counts, recv_displs, MPI_FLOAT, 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
		printf("Errore in MPI_Gatherv\n");
		free_all(m, r, send_counts, send_displs, recv_counts, recv_displs, input, output, rank, true);
		return 1; //MPI_Abort(MPI_COMM_WORLD, 1);
	}

    // if (rank == 0) {
    // 	for (int i = 0; i < len_r; i++) {
	// 	    if (!(i % dim_res)) printf("\n");
	// 	    printf("%f\t", r[i]);
    //     }
    //     printf("\n");
    // }
	
    free_all(m, r, send_counts, send_displs, recv_counts, recv_displs, input, output, rank, true);

	MPI_Barrier(MPI_COMM_WORLD);

	if (rank == 0) {
    	end = MPI_Wtime();
		printf("%d;%d;%f\n", dim, size, end - start);
    }

	MPI_Barrier(MPI_COMM_WORLD);

    if (MPI_Finalize() != MPI_SUCCESS) {
        printf("Errore in MPI_Finalize\n");
		return 1; //MPI_Abort(MPI_COMM_WORLD, 1);
    }
    return 0;
}
