# Cose da fare

- capire la consegna dell esercizio

- fare il codice che rislve l esercizio

- testarlo con le diverse dimensioni

- fare la presentazione



## Come facciamo a farli sembrare diversi?

- presentiamo implementazioni leggermente diverse della stessa idea

- testiamo su set di dati diversi

- la presentazione ha stile e impaginazine diverse

## PROPOSTA PROGETTO
Realizzare una soluzione parallela MPI nella quale:
- ogni nodo calcoli una diversa porzione della matrice risultato R
Pertanto:
- ogni nodo calcolerà gli elementi di  R della porzione assegnatagli utilizzando i corrispondenti elementi della matrice dei dati A;
- a questo scopo la matrice A verrà suddivisa tra tutti i nodi 

Al termine, il nodo «master» aggregherà i risultati prodotti da tutti i nodi nella matrice risultato.
[NB: decidere come gestire il calcolo degli elementi sul confine di ogni porzione]
- Realizzare una soluzione parallela OMP  che  calcoli la matrice R nella quale:
    - le matrici A e Rsiano condivise tra tutti i nodi;
    - ogni nodo calcolerà gli elementi di  R della porzione assegnatagli utilizzando i corrispondenti elementi della matrice dei dati A;
- Svolgere l’analisi delle prestazioni mediante scalabilità strong e weak di entrambe le soluzioni.

Entrambe le soluzioni dovranno essere PARAMETRICHE in:•N (-> allocazione dinamica delle matrici)
- p (numero dei thread/nodi)
Inoltre, dovrà essere sempre misurato il tempo di esecuzione.