#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int **allocaMatrice(int dimensione) {
    int **matrice = malloc(dimensione * sizeof(int *));
    for (int i = 0; i < dimensione; i++) matrice[i] = malloc(dimensione * sizeof(int));
    return matrice;
}

void deallocaMatrice(int **matrice, int dimensione) {
    for (int i = 0; i < dimensione; i++) free(matrice[i]);
    free(matrice);
}

void stampaMatrice(int **matrice, int dimensione) {
    for (int i = 0; i < dimensione; i++) {
        for (int j = 0; j < dimensione; j++) printf("%d\t", matrice[i][j]);
        printf("\n");
    }
    printf("\n");
}

void conferma_media(int somma, int i, int j) {
	 float media = somma / 9.0;
     printf("Elemento [%d][%d] -> Media 3x3: %.2f\n", i, j, media);
}

int somma_intorno_scorrimento(int **matrice, int somma_prima, int i_prima, int j_prima, int i_dopo, int j_dopo) {
    int somma = somma_prima;
    int direzione = j_dopo - j_prima;
    if (direzione) {
    	for (int k = -1; k < 2; k++) somma -= matrice[i_prima + k][j_prima - 1 * direzione];
    	for (int k = -1; k < 2; k++) somma += matrice[i_dopo + k][j_dopo + 1 * direzione];
    } else {
    	for (int k = -1; k < 2; k++) somma -= matrice[i_prima - 1][j_prima + k];
    	for (int k = -1; k < 2; k++) somma += matrice[i_dopo + 1][j_dopo + k];
    }
    return somma;
}

void media_intorno_processo(int **matrice, int righe, int colonne) {
	int somma = 0;
    for (int i = 1; i < righe - 1; i++) {
    	printf("Q");
        if (i % 2 == 1) for (int j = 1; j < colonne - 1; j++) {
			if (j == 1) somma = somma_intorno_scorrimento(matrice, somma, i - 1, j, i, j);
			else somma = somma_intorno_scorrimento(matrice, somma, i, j + 1, i, j);
			conferma_media(somma, i, j);
        } else for (int j = colonne - 2; j > 0; j--) {
		    if (j == colonne - 2) somma = somma_intorno_scorrimento(matrice, somma, i - 1, j, i, j);
			else somma = somma_intorno_scorrimento(matrice, somma, i, j - 1, i, j);
			conferma_media(somma, i, j);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Utilizzo: %s <dimensione> <elementi della matrice>\n", argv[0]);
        return 1;
    }
    int dimensione = atoi(argv[1]);
    if (dimensione <= 0) {
        printf("La dimensione deve essere un numero intero positivo.\n");
        return 1;
    }
    int thread = atoi(argv[2]);
    if (thread <= 0) {
        printf("I thread deve essere in quantità positiva.\n");
        return 1;
    }
    if (argc < 2 + dimensione * dimensione) {
        printf("Numero di elementi insufficiente per una matrice di dimensione %dx%d.\n", dimensione, dimensione);
        return 1;
    }

	int dimensione_risultato = dimensione / 2;
    int **A = allocaMatrice(dimensione);
    int k = 3;
    for (int i = 0; i < dimensione; i++) for (int j = 0; j < dimensione; j++) A[i][j] = atoi(argv[k++]);

    printf("Matrice %dx%d:\n", dimensione, dimensione);
    stampaMatrice(A, dimensione);
    printf("Matrice in alto a sinistra%dx%d:\n", dimensione_risultato, dimensione_risultato);
    stampaMatrice(A, dimensione_risultato);
    
    int colonne = thread > dimensione_risultato ? dimensione_risultato : sqrt(thread);
    int dimensione_colonna = dimensione_risultato / colonne;
    int colonne_grandi = dimensione_risultato % colonne;
    int righe = thread / colonne > dimensione_risultato ? dimensione_risultato : thread / colonne;
    int dimensione_riga = dimensione_risultato / righe;
   	int righe_grandi = dimensione_risultato % righe;
    
    printf("Colonne: %d %d %d\n", colonne, dimensione_colonna, colonne_grandi);
    printf("Righe: %d %d %d\n", righe, dimensione_riga, righe_grandi);
    
    media_intorno_processo(A, dimensione_risultato, dimensione_risultato);
    
    deallocaMatrice(A, dimensione);

    return 0;
}
