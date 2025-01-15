# Argomenti Principali

## Virtualizzazione

## Protezione

1. Quali sono le definizioni di protezione e di sicurezza, nel contesto dei sistemi operativi?
   
   La protezione consiste nell'insieme di attività volte a garantire il controllo dell'accesso alle risorse logiche e fisiche da parte degli utenti, mentre la sicurezza riguarda l'insieme delle tecniche con le quali regolamentare l'accesso degli utenti al sistema di elaborazione. La sicurezza impedisce accessi non autorizzati al sistema e i conseguenti tentativi dolosi di alterazione e distruzione dei dati.

2. Quali sono i meccanismi di sicurezza?
   
   I meccanismi di sicurezza sono: identificazione (chi sei?), autenticazione (come faccio a sapere che sei chi dici di essere?), autorizzazione (cosa puoi fare?).

3. Quali concetti chiave è necessario introdurre per descrivere il controllo degli accessi ad un sistema?
   
   E' necessario introdurre i concetti di: modelli, politiche e meccanismi. Un modello di protezione definisce i soggetti (attivi), gli oggetti (passivi) e i diritti di accesso dei soggetti (su oggetti o soggetti). Le politicha possono essere Discretional Access Control (DAC), Mandatory Access Control (MAC) o Role Based Access Control (RABC). I meccanismi di protezione sono gli strumenti che permettono di imporre una determinata politica e i principi sono la flessibilità del sistema di protezione e la separazione tra i meccanismi e le politiche.

4. Come è definito un dominio di protezione e cosa si intende per oggetto condiviso?
   
   Un dominio di protezione definisce un insieme di coppie, ogniuna contenente l'identificatore di un oggetto e l'insieme delle operazioni che il soggetto associato al dominio può eseguire su quell'oggetto. Chiaramente è unico per ogni soggetto, mentre un processo può cambiare dominio durante la sua esecuzione. Si intende per oggetto condiviso un oggetto che compare in diversi domini di protezione associati a soggetti diversi; che lo condividono (alternativa: domini disgiunti).

5. Sai mettere in relazione degli esempi, in cui il cambio di dominio è fondamentale, con il principio del privilegio minimo?
   
   Lo standard dual mode distingue tra user mode e kernel mode con un cambio di dominio associato alle system call. In Unix il dominio è associato all'utente ed è possibile un cambio di contesto grazie ai bit UID e GID. In questi casi si dice che l'associazione tra processo e dominio è dinamica, altrimenti è statica. Il principio del privilegio minimo, secondo cui ai soggetti sono garantiti solo gli oggetti strettamente necessari per la sua esecuzione, si sposa perfettamente col concetto di dominio di protezione dinamico.

6. Quali sono i pro e i contro dei due modi di propagazione di un diritto?
   
   Un diritto può esssere propagato per trasferimento o per copia e la differenza è che nel primo caso chi trasferisce perde il diritto. La propagazione per trasferimento permette di rispettare i vincoli legali o tecnici garantendo l'esclusività della licenza o del diritto. La possibilità di copiare un diritto è determinata dal copy flag (*).

7. Sai spiegare il significato dei diritti owner, control, switch?
   
   Chi possiede il diritto owner può assegnare o revocare qualunque diritto di accesso sull'oggetto di cui è proprioetario. Chi possiede il diritto control può revocare qualunque diritto di accesso su qualunque oggetto al soggetto che controlla. Chi possiete il diritto switch su un altro soggetto può commutare il proprio dominio nel dominio del soggetto in questione (permesso anche il ritorno).

8. Quale sarebbe il probelma se la matrice degli accessi non ci fosse?
   
   Non sarebbe possibile verificare se un accesso è consentito o meno, nè cambiare il dominio dinamicamente. Non sarebbe possibile cambiare lo stato di protezione in modo controllato e non sarebbero noti i soggetti e gli oggetti del sistema.

9. Quali sono i pregi e i difetti delle diverse implementazioni della matrice degli accessi in un sistema operativo?
   
   Se si implementa come access control list (ACL) allora è semplice aggiungere o rimuovere oggetti ma è impegnativo aggiungere o togliere soggetti. Nel caso delle Capability List (CL) è il contrario. La revoca dei diritti di accesso può essere generale o selettiva, parziale o totale, temporanea o permanente; con ACL risulta semplice, con CL risulta compessa. La soluzoine ideale è quella mista: la ACL è persistente e quando un soggetto accede ad un oggetto, la si controlla una sola volta e si aggiorna la CL del soggetto, che viene distrutta solo dopo l'ultimo accesso del soggetto.

10. Nel contesto dei sistemi multilivello, quale è il significato di clarance levels, sensitivity levels, security levels e category set?
    
    Rispettivamente sono i livelli per i soggetti, i livelli per gli oggetti, i livelli per la classificazione gerarchica della riservatezza (non classificato, confidenziale, segreto, top secret) e un insieme di categorie dipendenti dall'applicazione in cui i dati sono usati.

11. Perchè il modello Biba è debole all'attacco del cavallo di Troia mentre il modello  Bell-La Padula invece no?
    
    I due modelli sono caratterizzati dalle rispettive proprietà di sicurezza semplice e di integrità *. Nel Bell-La Padula il flusso delle informazioni è verso l'alto dal momento che si può leggere verso il basso e scrivere verso l'alto mentre nel Biba è il contrario. Nel attacco del cavallo di Troia l'attaccante tenta con l'inganno di far eseguire a chi ha più privilegi ed informazioni di lui un programma che scrive queste informazioni in un file non classificato di modo da poterle leggere, ma non funziona sempre; il flusso di informazioni verso l'alto garantisce confidenzialità, mentre il flusso verso il basso garantisce integrità.

12. Perchè tutti i sistemi ad alta sicurezza sono sistemi fidati?
    
    Per i sistemi fidati è possibile definire formalmente dei requisiti di sicurezza e la presenza dei requisiti è necessaria per poterli classificare come "elevata sicurezza".

13. Che legame c'è tra TCB e l'audit file?
    
    Il Trusted Computing Base contiene i privilegi di sicurezza di ogni soggetto e gli attributi di protezione di ogni oggetto, mentre nell'audit file vengono mantenuti gli eventi importanti come i tentativi di violazione della sicurezza o le modifiche autorizzate al TCB stesso.

14. Nei sistemi ad elevata sicurezza, cosa garantisce il reference monitor?
    
    Garantisce: mediazione completa, applicando le regole di sicurezza ad ogni accesso e non solo, isolamento proteggendo reference monitor e base di dati da modifiche non autorizzate,  e infine verificabilità delle precedenti.

15. Quali sono le principali categorie dell'Orange Book?
    
    D (Minimal Protection), C (Discretional Protection), B (Mandatory Protection), A (Verified Protection).

## Programmzione Concorrente

## Modello a Memoria Comune

## Nucleo Sistema Memoria Comune

## Modello Scambio di Messaggi

## Comunicazione Sincronizzazione Estesa

## Implementazioni Concorrenza

## Algoritmi Sincronizzazione Distribuiti

1. Quale è il legame tra modello a scambio di messaggi e sistema distribuito?
   
   Il modello a scambio di messaggi è la naturale astrazione di un sistema
   distribuito, nel quale processi distinti eseguono su nodi fisicamente separati,
   collegati tra di loro attraverso una rete. Nel sistema distribuito non ci sono risorse condivise e non c'è un glock globale. Si passa dla concorrente al distribuito e si introduce la possibilità di malfunzionamenti indipendenti.

2. Quali sono le proprietà desiderabili nel distribuito?
   
   Salabilità e tolleranza ai guasti. La scalabilità garantisce che nell’applicazione distribuita le prestazioni aumentano al crescere del numero di nodi utilizzati. La tolleranza ai guasti garantisce che l’applicazione è in grado di funzionare anche in
   presenza di guasti (es. crash di un nodo, problemi sulla rete, ecc.).

3. Come si misurano le prestazioni di un sistema distribuito?
   
   Lo speedup e l'efficienza sono indicatori usati e idelmente hanno rispettivamente valore $n$ ed $1$.
   
   $$
   Speedup(n)=\frac{Tempo(1)}{Tempo(n)} \newline
Efficienza(n)=\frac{Speedup(n)}{n}
   $$

4. Quali spossono essere i tipi di guasto e cosa si intende come si implementa la tolleranza ai guasti?
   
   I guasti possono essere transienti, intermittenti o persistenti. Si possono implementare tecniche di ridondanza e sono necessari meccanismi di rilevazione (fault detection) e di riprestino (recovery).

5. Come è organizzata la gestione del tempo in un sistema distribuito?
   
   Ogni nodo è dotato di un suo orologio. Se gli orologi locali di due nodi non sono sincronizzati, è possibile che due eveti in due nodi diversi siano associati a due istanti temporali che fanno semprare che uno sia precedente all'altro quando in realtà è il contrario. Nel caos isa necessario un riferimento temporale unico e si può usare un orologio universale fisico (algoritmi di Berkley e Cristian) o un orologio logico; che permette di associare ad ogni eventi un istant e logico (timestamp) la cui relazione coi timestamp di altri eventi sia coerente con l'ordine in cui essi si verificano.

6. Come si possono caratterizzare i eventi concorrenti?
   
   E' possibile definire la relazione di precedenza tra eventi (Heppende Before, $->$). Data una coppia di eventi $a$ e $b$, allora se $a$ precede $b$ si indica con $a->b$, se invece $a$ precede $a$, si indica con $b->a$, e infine se nessuna delle due è valida allora sono concorrenti.

7. Come funziona l'algoritmo di Lamport?
   
   Ogni processo mantiene localmente un contatore del tempo logico e ogni nuovo evento all'interno del processo provoca un incremento del valore del contatore. Inoltre Ogni volta che il processo vuole inviare un messaggio, dopo aver incrementato il contatore, quest'ultimo viene allegato al messaggio. Quando si riceve un messaggio si assegna al proprio contatore il massimo tra il valore del contatore allegato e il valore attuale, e successivamene lo si incrementa. Usualmente implementato dal middleware che interfaccia i precessi alla rete.

8. Come possiamo classificare le soluzoini volte a garantire che due o più processi non possano eseguire contemporaneamente alcune prestabilite attività?
   
   Per risolvere la mutua esclusione distribuita si può ricorrere a soluzoni token-based o permission-based e queste ultime a loro volta possono essere centralizzate oppure decentralizate.

9. Quali sono vantaggi e svantaggi della soluzioni permission-based centralizzata?
   
   L'algoritmo è equo quindi non c'è starvation. E' anche semplice perchè prevede solo 3 messaggi: richiesta, autorizzazione e rilascio. Purtroppo non è né scalabile né tollerante ai guasti. Un procesos che non riceve autorizzazione non può sapere se non è stata concessa o se il gestore è guasto.

10. Quale dell'algoritmo permission-based è scalabile e cosa possiamo dire sulla sua tolleranza ai guasti?
    
    L'algoritmo Ricard-Agrawala prevede $2*(N-1)$ messaggi per ogni sezione critica. Inoltre la tolleranza ai guasti è pessima perchè è sufficiente che ci sia un guasto su un nodo e nessuno sarà più autorizzato a fare nulla. Si può fare una piccola modifica introducento i messaggi di accesso negato. Una volta ricevuti ci si mette di nuovo in attesa ma si può impostare un timeout per rilevare i guasti e eventualmente escluderlo dal gruppo.

11. Quaii osno gli aspetti cruciali dell'algoritmo token ring?
    
    L'intero sistema è costruito da un insieme di processi in competizione collegati tra loro in una topologia ad anello e i processi conoscono i loro vicini. Un messaggio, detto token, circola attraverso l'anello, nel verso relativo all'ordine dei processi nella topologia. Chi deve eseguire la sezione critica tiene il token fino al rilascio. E' scalabile ma ci possono essere moltissimi messaggi per ogni sezione critica. Inoltre ci sono N punti di fallimento e un crash può fare perdere il token.

12. Cosa è un algoritmo di elezione?
    
    In alcuni algoritmi è necessario che un processo svolga il ruolo di coordinatore. La disegazione può essere statica o dinamica. Nel secondo caso, per scegliere, si usa un algoritmo di elezione.

13. Quali sono le differenze tra gli algoritmi di elezione Bully ed ad Anello?
    
    Nel primo il processo che avvia l'elezione invia l'aposito messaggio a tutti i processi con l'id più alto del suo e chi non è guasto risponde positivamente. Poi se c'è stata almeno una risposta, tutti quelli che hanno risposto avviano un elezione a loro volta. Nel secondo caso quando un processo si rende conto che il coordinatore è guasto inizia un elezione mandando un messaggio col priprio id e chi lo riceve aggiunge il proprio id e lo riinvia a sua volta. Quando si riceve un messaggio con proprio id si cambia il contenuto del messaggio e si invia ora l'identità del nuovo coordinatore, ovvero l'id più alto tra tutti.

## Introduzione HCP

1. Quali sono le differenze tra il calcolo concorrente e il calcolo parallelo?
   
   In entrambi i casi si da luogo ad un insieme di attività. Sono concorrenti se sono contemporaneamente in progress, ovvero iniziate ma non temrinate, sono parallele se effettivamente le attività multiple eseguono in contemporanea.
   
   Nel primo caso il numero di processori è maggiore del numero delle CPU, nel secondo invece no. 

2. Perchè si esegue in parallelo?
   
   Per aumentare le performance in temini di complessità dei problemi che si possono risolvere e di tempo necessario.

3. Cosa ci dice la Legge di Moore sull'evoluzione dei sistemi di calcolo nel tempo?
   
   Fino ai primi anni 2000 l'evoluzione dei sistemi di calcolo seguivano un andamento preciso: in numero di transistori in ogni 18 mesi. Quando poi si sono raggiunti i limiti fisici legati all' effeto Joule e non è stato più possibile aumentare la frequenza di clock è stato necessario aumentare la capacità di calcolo a parità di frequenza. Il parallelismo in questo senso è diventato una forma di accellerazione dell'hardware.

4. Cosa si intende con Von Neumann Bottleneck?
   
   La velocità di fetching di istruzioni e dati diepden dalla velocità di trasmissione del Bus è una limitazione della velcità di esecuzione. Il modello di Von Neumann è stato quindi esteso con l'introduzione di memorie cache e di paralllelismo di basso livello, come Instruction-level parallelism (ILP) e HW multithreading (TLP). Il modello Von Neumann esteso è trasparente per lo sviluppatore.

5. La cache che tipo di memoria è?
   
   E' una memoria associativa ad accesso veloce e di capacità limitata che risiede sul chip del processore e si colooca ad un livello intermedio tra i registri e la memoria centrale. Viene gestita con criteri sul principio di località spaziale e temporale (cache hit/miss ed hit-rate).

6. Cosa si intende con parallelismo a livello di istruzione?
   
   L'esecuzione di ogni istruzione viene attuata attraverso una sequenza di fasi. Ogni fase può essere affidata ad un unità funzionale indipendente che opera in parallelo alle altre. Si possono mettere in pipelining collegando tutte le unità funzionali tra loro eseguendo fasi diverse di istruzioni diverse in parallelo. In alternativa ci possono essere più istanze di ogni unità funzionale.

7. Cosa si intende con hardware multi-threading?
   
   Permette a due thread di condividere la stessa CPU (core), utilizzando una tecnica di sovrapposizione. Ciò è reso possibile dalla duplicazione dei registri che mantengono lo stato di ogni thread (PC, IR, ecc) e da un meccanismo HW che implementa il context switch tra un thread ed un altro in modo molto efficiente. Sono possibili 2 approcci: a grana fine e a grana grossa. Nel primo caso viene eseguito context switch dopo ogni istruzione e nel secondo viene eseguito context switch quando il thread corrente è in una situaizone di attesa.

8. Come si realizza la parallelizzazione esplicita?
   
   SI possono usare 2 modelli: scambio di messaggi (MPI) o memoria condivisa (OpenMP). Il parallelismo si ottiene distribuendo task diversi a processi diversi; ogni processo è assegnato a una CPU a sua completa disposizione. Normalmente su utilizza il paradigma SPMD (single program multiple data) sfruttando il branching condizionale. Solo pochi programmi sono embarassingly parallel, nella maggior parte dei casi le iterazioni non sono indipendenti tra loro ed è necessaria che i processi siano sincronizzati. Quindi prima s i divide il lavoro e ppoi ci si occupa di sincronizzazione e comunicazione.

9. Cosa sono i petaFLOPS e gli exaFLOPS?
   
   Sono unità di misura delle prestazioni ovvero i floating point operations per second. Corrispondono rispettivamente a $10^{15}$ e a $10^{18}$ FLOPS.

10. Quale è il legame tra speedup ed efficienza?
    
    Lo speedup misura quanto è più veloce la versione parallela rispetto alla versione sequenziale, ovvero il guadagno della parallelizzazione e nel caso ideale vale 1. Nei casi non ideali c'è overhead dovuto alla creazione e allocazione dei processi, alla cominicazione e alla sincronizzazione e anche alla distribuzione non bilanciata del lavoro. L'efficienza serve a misurare la scalabilità: quanto più rimane costate tanto più un programma è scalabile.

11. Quando si misura la scalabilità quali opzioni si hanno?
    
    Si può misurare la scalabilità strong, ovvero quanto si può guadagnare nella soluzione di uno stesso problema di dimensione fissata aumentando il numero di processori, oppure la scalabilità weak, ovvero se è possibile risolvere lo stesso problema di dimensioni maggiori nello stesso tempo.

12. Cosa dice la Legge di Amdahl e cosa ci dice sulla saclabilità strong?
    
    Partendo dalla premessa che non tutto un programma è parallelizzabile, si calcola lo speedup in funzione di $r$ ovvero della frazione del tempo totale di esecuzione spesa nella parte non parallelizzabile e si ottinene $\lim_{p \to \infty} S = \frac{1}{r}$ ; ovvero se $r$ e diverso da 0, lo speedup non può crescere all'infinito. Similmente vale $\lim_{p \to \infty} E = 0$ il che ci conferma che solo nel caso ideale al crescere di p, l'efficienza si mantiene costante.

13. Come si valuta la scalabilità weak?
    
    Si usano efficienza scalata e speedup scalato:
    
    $$
    E_s(p, N) = \frac{T(N, 1)}{T(pN, p)} \newline
S_s(p, N) = E_sp
    $$

14. Cosa implica la Legge di Gustafson?
    
    La Legge di Gustafson presuppone che il probelma sia di dimensione variabile e si concentra sulla scalabilità weak. implica che assegnando ad ogni processore un workload costante (1-r), lo speedup cresce linearmente con il numero dei processori.
    
    $$
    S(p, pN) = \frac{T(1, pN)}{T(p, pN)} \newline
da \space cui \newline
S(p, pN) = r + (1 - r)p
    $$

## Programmazione Parallela con MPI

1. In quale ambito lo standard è rappreesentato dalle librerie MPI?
   
   Se i nodi dell'architettura non condividono memoria e lo sviluppo dei programmi paralleli si fonda sul modello a scambio di  messaggi (esempio Cluster HPC).

2. Quali sono le caratteristiche principali dello standard Message Passing Interface?
   
   E' basato sul paradigma SPMD con molteplici istanze dello stesso programma, ogniuna in esecuzione contemporanea su un nodo distinto. Ogni istanza rappresenta un processo MPI. Offre un ricco set di funzioni per esprimere comunicazione tra processi sia punto-punto che collective, con semantiche sia sincrone che asincrone. Offre inoltre potenti strumenti per data partitioning e data collecting e gestisce i processi in maniera statica e implicita definendo il grado di parallelismo a tempo di caricamento.

3. Cosa sono i comunicator?
   
   Sono astrazioni che definiscono un dominio di comunicazione, ovvero un insieme di processi che possono comunicare tra loro; due processi possono scambiarsi messaggi solo se appartengono allo stesso comunicator. Esiste un comunicator di default detto MPI_COMM_WORLD. A partire da questo è possibile crearne di altri.

4. Quali sono i limiti della soluzioni centralizzate e cosa si può fare per superarli?
   
   Al crescere del numero dei nodi il master potrebbe rappresentare un collo di bottiglia, dovendo ricevere molti messaggi. Per mitigari, si può distribuire il carico di comunicazione tra più nodi utilizzando degli schemi di comunicaizone gerarchici che coinvolgono tutti i nodi. Ogni nodo dell’albero riceve messaggi dai nodi figli e manda un messaggio «cumulativo» al padre. In questo modo il master viene alleggerito.

5. Quali sono le intestazioni delle funzioni principali di MPI?

```c
int MPI_Init(int* argc, char*** argv);

int MPI_Finalize(void);

int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm* new_comm);

int MPI_Comm_spawn(const char* command, char* argv[],
int maxprocs, MPI_Info info, int root, MPI_Comm comm,
MPI_Comm* intercomm, int array_of_errcodes[]);

int MPI_Comm_size(MPI_Comm comm, int* size);

int MPI_Comm_rank(MPI_Comm comm, int* rank);

int MPI_Send(const void* buffer, int count, MPI_Datatype datatype,
int dest, int tag, MPI_Comm comm);

int MPI_Ssend(const void* buffer, int count, MPI_Datatype datatype,
int dest, int tag, MPI_Comm comm);

int MPI_Isend(const void* buffer, int count, MPI_Datatype datatype,
int dest, int tag, MPI_Comm comm, MPI_Request* request);

int MPI_Bsend(const void* buffer, int count, MPI_Datatype datatype,
int dest, int tag, MPI_Comm comm);

int MPI_Wait(MPI_Request* request, MPI_Status* status);

int MPI_Test(MPI_Request* request, int* flag, MPI_Status* status);

int MPI_Recv(void* buffer, int count, MPI_Datatype datatype, int source,
int tag, MPI_Comm comm, MPI_Status* status);

int MPI_Irecv(void* buffer, int count, MPI_Datatype datatype, int source,
int tag, MPI_Comm comm, MPI_Request* request);

int MPI_Reduce(const void* send_buffer, void* receive_buffer, int count,
MPI_Datatype datatype, MPI_Op operation, int root, MPI_Comm comm);

int MPI_Ireduce(const void* send_buffer, void* receive_buffer,
int count, MPI_Datatype datatype, MPI_Op operation, int root,
MPI_Comm comm, MPI_Request* request);

int MPI_Allreduce(const void* sendbuf, void* recvbuf, int count,
MPI_Datatype datatype, MPI_Op operation, MPI_Comm comm);

int MPI_Bcast(void* buffer, int count, MPI_Datatype datatype,
int emitter_rank, MPI_Comm communicator);

int MPI_Scatter(const void* sendbuf, int count_send,
MPI_Datatype datatype_send, void* recvbuf, int count_recv,
MPI_Datatype datatype_recv, int root, MPI_Comm comm);

int MPI_Gather(void* sendbuf, int count_send,
MPI_Datatype datatype_send, void* recvbuf, int count_recv,
MPI_Datatype datatype_recv, int root, MPI_Comm communicator);

int MPI_Barrier(MPI_Comm comm);

double MPI_Wtime(void);
```

## Programmazione Parallela con OpenMP

1. Quali modelli si possono utilizzare in caso di memoria condivisa ra i processi?
   
   Si possono usare si il modello a scambio di messaggi, ad esempio con MPI, che il modello a memoria condivisa. In questo ultimo caso si possono usare diverse tecnologie: i sistemi multicore o multiprocessor come OpenMP o pthreads oppure le GP-GPU per le quali esistono librerie specifiche che consentono lo sviluppo di programmi destinati ad eseguire su GPU come CUPA (libreria proprietaria NVidia) oppure openCL.

2. Quali sonole caratteristiche principali di OpenMP?
   
   E' una libreria che permette di parallelizzare il codice di programmi C, utilizzando un approccio dichiarativo. Offre strumenti per gestire i thread paralleli, ottenere/impostare informazioni sull'ambiente di esecuzione, definire la visibilità delle variabli rispetto ai thread paralleli e di sincronizzare i thread tra loro con sezioni critiche o bariere di sincronizzazione.

3. Quali sono le clausole principali della direttiva parallel?
   
   Sono diverse. Con num_threads(N) si imposta il numero di thread paralleli. Usando shared private e firstprivate (ogni processo utilizza una copia privata inizializzata al valore che aveva prima di pragma) si può specificare il campo di visibilità (mentre di default la variabili sono private solo se definite internamente al blocco parallel, private altrimenti). Con reduction è possibile utilizzare una variabile di appoggio permettendo di valutare l'espessione in parallelo (aggiornamento di var in mutua esclusione). Con if si rende condizionale la parallelizzazione, se false allora l'esecuzione è sequenziale. Con for è possibile parallelizzare un ciclo e usando schedule ci si può assicurare di bilanciare il carico che può essere static o dynamic.

4. Come si possono gestire le informazioni sui thread in esecuzione?
   
   ```c
   #include <omp.h>
   
   #pragma omp parallel
   {
       // Restituisce il numero di thread paralleli
       // da utilizzare all'interno di un blocco parallelo
       int num_threads = omp_get_num_threads();
   
       // Restituisce il rank del thread che lo invoca (0 è il master)
       int thread_id = omp_get_thread_num();
   
       // Imposta a n il numero di thread paralleli
       // nei successivi blocchi paralleli
       omp_set_num_threads(4);
   }
   
   ```

5. A cosa servono le direttive master e single?
   
   La direttiva master indica che solo il thread master (tipicamente il thread che ha un ID pari a 0)mentre la direttiva single crea una barierea di sincronizzazione implicita, garantendo che solo un thread, scelto arbitrariamente, esegua il blocco di codice.

6. Quali clausole hanno come scopo principale la sincronizzazione?
   
   La prima è la direttiva critical: il blocco di istruzioni immediatamente successivo alla direttiva viene eseguito un solo processo alla volta. Anche la direttiva barrier è utile ed implmenta la classica barriera di sincronizzazione in un team di threads. Inoltre è possibile usare i lock per reealizzare schemi di sincronizzaizone ad hoc.
   
   ```c
   //esattamente equivalente a critical
   #include <stdio.h> #include <omp.h>
   omp_lock_t my_lock;
   int main() {
       omp_init_lock(&my_lock);
       #pragma omp parallel num_threads(4)
       {
           int i, j, t = omp_get_thread_num( );
           for (i = 0; i < 5; ++i) {
               omp_set_lock(&my_lock); //prologo sezione critica
               printf("Thread %d – inizio sezione critica %d\n", t,i);
               printf("Thread %d - fine sezione critica %d\n", t, i);
               omp_unset_lock(&my_lock); //epilogo sezione critica
           }
       }
       omp_destroy_lock(&my_lock);
   }
   ```

7. Come si può misurare il tempo?
   
   ```c
   double omp_get_wtime(void);
   ```

8. Quali osservazioni possiamo fare paragonando OpenMP ad altre librerie come pthread oppure MPI?
   
   Pthread utilizza un paradigma MPMD ed un modello di creazione fork-join. Mette a disposizione un ampio set di politiche per la sinconizzazione specifiche (mutex, semafori, condition) e risulta particolarmente adatto per algoritmi task-parallel. OpenMp a confronto utilizza un approccio di più alto livello, basato su SPMD ed un modello di crreazione cobegin-coend. La sincronizzazione avviene tramite direttive e clausole che implemntano schemi predefiniti (barrier, critical, reduction), o anche ad hoc coi lock. Ideale per la modellazione di algoritmi data-parallel.
   
   Se mettiamo a confronto OpenMP con MPI è evidente che il primo è ben più semplice da utilizzare (vedi bilalnciamento del carico) e che il secondo, insieme alla complessità di utilizzo, ha tra le sue proprietà una maggiore scalabilità e portabilità.Da notare che è possibile combinare i due e beneficiare dei vantaggi di entrambi: si parla di Hybridization.
