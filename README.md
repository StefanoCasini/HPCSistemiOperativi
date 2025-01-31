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

## Stato progetti 

- MPI -> il codice è stato testato su galileo, occorre modifica per far si che un processo possa prendere più di una riga, quando il numero di processi non è uguale al numero delle righe della matrice
    - POSSIBILE SOLUZIONE -> sfruttare il fatto che la matrice sia linearizzata, quindi sostanzialmente è possibile dare al processo più di una riga (3 righe in totale dove calcola gli elementi di quella centrale), occorre solamente verificare che la somma successiva non sia la prima della riga dopo, siccome il primo elemento è uno zero, e a questo punto diciamo ricalcolare la somma del primo elemento come la somma del rettangolo 2*3 (dove l'elemento preso nello specifico si trova in riga 1 in colonna 0, 0 rispetto a tabella indicata)
    NB. Ad ogni Thread possiamo comunque pensare di mandare le righe intere, quindi diciamo che alcuni thread faranno proprio il calcolo di più righe, oppure ogni thread si prende un certo pezzo dell'array linearizzato e noi dobbiamo solamente controllare che non calcoli il primo e l'ultimo elemento della colonna se lo ha.
    - ALTERNATIVA -> cercare di improntare una soluzione sulla base dei quadrati che avevamo pensato inizialmente, probabilmente è fattibile, sfruttando una caratteristica di Scatterv (da controllare però), soluzione meno facile da implementare

- OMP -> problemi su calcolo numero di colonne e di righe, (da segmentation fault siccome ci sono errori negli indici), compila se la graffa dopo pragma è messa nella linea sotto (a capo)
    - aggiungere parte che se il numero di thread è maggiore del numero di elementi usa al massimo un thread per elemento      