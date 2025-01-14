//la matrice è di float in realtà

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int **alloca_inizializza_matrice(char *argv[], int dimensione) {
	int dimensione_risultato = dimensione / 2 + 2;
    int **matrice = malloc(dimensione_risultato * sizeof(int *));
    for (int i = 0; i < dimensione_risultato; i++) matrice[i] = malloc(dimensione_risultato * sizeof(int));
    for (int i = 0; i < dimensione_risultato; i++) matrice[i][0] = matrice[0][i] = 0;
    int c = 3;
    for (int i = 1; i < dimensione_risultato; i++) {
    	for (int j = 1; j < dimensione_risultato; j++) matrice[i][j] = atoi(argv[c++]);
    	c = 3 + dimensione * i;
    }
    return matrice;
}

void dealloca_matrice(int **matrice, int dimensione) {
    for (int i = 0; i < dimensione; i++) free(matrice[i]);
    free(matrice);
}

void stampa_matrice(int **matrice, int dimensione) {
    for (int i = 0; i < dimensione; i++) {
        for (int j = 0; j < dimensione; j++) printf("%d\t", matrice[i][j]);
        printf("\n");
    }
    printf("\n");
}

void dividi_matrice(int **matrice, int i_inizio, int i_fine, int j_inizio, int j_fine) {
	int **divisa = malloc((i_fine - i_inizio + 3) * sizeof(int *));
	for (int i = 0; i < i_fine - i_inizio + 3; i++) divisa[i] = malloc((j_fine - j_inizio + 3) * sizeof(int));
	for (int i = i_inizio - 1; i <= i_fine + 1; i++) {
		for (int j = j_inizio - 1; j <= j_fine + 1; j++) {
			divisa[i - i_inizio + 1][j - j_inizio + 1] = matrice[i][j];
			printf("%d\t", divisa[i - i_inizio + 1][j - j_inizio + 1]);
		}
		printf("\n");
	}
	printf("\n");
	for (int i = 0; i < i_fine - i_inizio + 3; i++) free(divisa[i]);
    free(divisa);
}

void conferma_media(int **matrice, int somma, int i, int j) {
	 float media = somma / 9.0;
     printf("Elemento [%d][%d]: %d -> Media 3x3: %.2f\n", i, j, matrice[i][j], media);
}

int somma_intorno_prima(int **matrice, int somma_prima, int i, int j) {
	int somma = 0;
	for (int ik = -1; ik < 2; ik++) for (int jk = -1; jk < 2; jk++) somma += matrice[i + ik][j + jk];
	return somma;
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
        if (i % 2 == 1) for (int j = 1; j < colonne - 1; j++) {
        	if (i == 1 && j == 1) somma = somma_intorno_prima(matrice, somma, i, j);
			else if (j == 1) somma = somma_intorno_scorrimento(matrice, somma, i - 1, j, i, j);
			else somma = somma_intorno_scorrimento(matrice, somma, i, j - 1, i, j);
			conferma_media(matrice, somma, i, j);
        } else for (int j = colonne - 2; j > 0; j--) {
		    if (j == colonne - 2) somma = somma_intorno_scorrimento(matrice, somma, i - 1, j, i, j);
			else somma = somma_intorno_scorrimento(matrice, somma, i, j + 1, i, j);
			conferma_media(matrice, somma, i, j);
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
    int **A = alloca_inizializza_matrice(argv, dimensione);

    printf("Matrice in alto a sinistra %dx%d con bordo aggiunto:\n", dimensione_risultato, dimensione_risultato);
    stampa_matrice(A, dimensione_risultato + 2);
    
    int colonne = thread > dimensione_risultato ? dimensione_risultato : sqrt(thread);
    int dimensione_colonna = dimensione_risultato / colonne;
    int colonne_grandi = dimensione_risultato % colonne;
    int righe = thread / colonne > dimensione_risultato ? dimensione_risultato : thread / colonne;
    int dimensione_riga = dimensione_risultato / righe;
   	int righe_grandi = dimensione_risultato % righe;
    
    printf("Colonne: %d %d %d\n", colonne, dimensione_colonna, colonne_grandi);
    printf("Righe: %d %d %d\n", righe, dimensione_riga, righe_grandi);
    
    dividi_matrice(A, 1, 1, 1, 1); 
    
    media_intorno_processo(A, dimensione_risultato + 2, dimensione_risultato + 2);
    
    dealloca_matrice(A, dimensione_risultato + 2);

    return 0;
}
