#include "library.h"

void fileCreator() {

    //Questa prima funzione si occupa, nel caso in cui l'utente voglia aggiugere da terminale dei file alla cartella
    //obiettivo, d'istanziare dei file dati in immissione nome e contenuto

    char pw[10], social[20];
    int index=0;

    printf("Inserisci il nome del servizio: \n");
    scanf("%s", social);
    printf("Inserisci la password del servizio: \n");
    scanf("%s", pw);
    printf("File %s with pw: %s \n", social, pw);
    printf("--------------------------------- \n");

    //puntatore all'ID di stream del file
    FILE *bebo;

    //tentativo di apertura che in caso non esista il file obiettivo si risolve nella creazione dello stesso
    bebo = fopen(social, "w");

    //controllo se l'apertura sia andata a buon fine
    if (bebo != NULL) {

        //scorro la stringa fino a che non è vuota la posizione corrente scrivendo carattere per carattere
        for (int i = 0; pw[i] != NULL; i++) {
            fprintf(bebo, "%c", pw[i]);
        }
    } else {
        //errore generico in caso l'apertura non vada a buon fine
        perror("File non creato");
    }
    //scrivo anche un ultimo carattere dato che la funzione di lettura arriva fino al penultimo carattere
    fprintf(bebo,"%c",'.');
    fclose(bebo);
}

int fileCounter() {

    //funzione che si occupa di esplorare la cartella obiettivo e restituire il numero di file
    //al suo interno tramite lo stream della stessa

    //variabile che conterrà il numero di file trovati
    int numeroFile = 0;

    //puntatore alla stream della cartella e struct che conterrà volta per volta le informazioni del file
    //che viene iterato
    DIR *dirp;
    struct dirent *entry;

    //apro la stream della cartella corrente
    dirp = opendir(".");

    //controllo la corretta apertura della cartella e mi muovo di conseguenza
    if (dirp == NULL) {
        //errore generico in casola cartella non si apra
        perror("Cartella non aperta");
    } else {
        //itero la cartella
        while ((entry = readdir(dirp)) != NULL) {

            //controllo se il file in esamina è del tipo voluto e in caso incremento il counter
            if (entry->d_type == DT_REG) {
                numeroFile++;
            }
        }
        //chiudo la stream della cartella
        closedir(dirp);
    }
    //ritorno il numero di file che sono in cartella
    return numeroFile;
}

void fileLister(char *nomeArray[]) {

    //questa funzione scorrendo tra i file già contati di una cartella e associa il nome di ognuno di essi
    //a un puntatore di un array di puntatori in modo così da poter richiamare quando si vuole il file tramite il suo
    //nome in ognuna altra funzione del programma.

    //variabile che contiene l indice di scorrimento nell'array
    int indiceArray = 0;

    //puntatore alla stream della cartella e struct che conterrà volta per volta le informazioni del file
    //che viene iterato
    DIR *dp;
    struct dirent *ep;

    //apro la stream della cartella corrente
    dp = opendir(".");

    //controllo la corretta apertura della cartella e mi muovo di conseguenza
    if (dp != NULL) {
        //itero la cartella
        while ((ep = readdir(dp)) != NULL) {

            //controllo che il file iterato sia del tipo giusto
            if (ep->d_type == DT_REG && strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0) {

                //assegno il nome del file alla posizione dell'array in cui siamo arrivati
                nomeArray[indiceArray] = ep->d_name;
                //incremento l'indice di scorrimento dell'array per una nuova iterazione
                indiceArray++;
            }
        }
        //chiudo la cartella
        closedir(dp);
    } else {
        //errore generico nel caso in cui non si apra la cartella
        perror("Non ho potuto aprire la cartella");
    }
}

void fileScroller(void) {

    //questa funzione scorrendo tra i file già contati di una cartella e associa il nome di ognuno di essi
    //a un puntatore di un array di puntatori in modo così da poter richiamare quando si vuole il file tramite il suo
    //nome in ognuna altra funzione del programma.

    //puntatore alla stream della cartella e struct che conterrà volta per volta le informazioni del file
    //che viene iterato
    DIR *dp;
    struct dirent *ep;

    //apro la cartella
    dp = opendir(".");

    //controllo che si sia aperta correttamente
    if (dp != NULL) {
        //itero la cartella
        while ((ep = readdir(dp)) != NULL) {
            //controllo che il file iterato sia del tipo esatto per la lettura scrittura
            if (ep->d_type == DT_REG && strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0) {

                //chiamo la funzione di lettura cript e scrittura sul file iterato
                hashEncoder(ep->d_name);

                //do un tempo di wait arbitrario per permettere un monitoring più ordinato dell'iterazione
                sleep(2.0);
            }
        }
        //chiudo lo stream della cartella
        closedir(dp);
    } else {
        //errore he viene stampato in caso la cartella non si apra
        perror("Non ho potuto aprire la cartella");
    }
}

void hashEncoder(char nomeFile[]) {

    //stringa che conterrà la password letta dal file
    char testoChiaro[30];
    //indice che determina la lunghezza della password letta
    int index = 0;
    //password usata per l'hashing
    const char passphrase[] = {"pucci"};

    //puntatore di lettura
    FILE *fileIDread;
    //puntatore di scrittura
    FILE *fileIDwrite;

    //tento l'apertura del file
    fileIDread = fopen(nomeFile, "r");
    //controllo sia aperto correttamente
    if (fileIDread) {

        printf("File: %s \n", nomeFile);
        printf("Puntatore buono \n");

        //leggo il primo valore del file
        fscanf(fileIDread, "%c", &testoChiaro[index]);
        //itero tutto il file fino a che non mi restituisce il feof
        while (!feof(fileIDread)) {
            //incremento prima il counter dato che ho già letto un valore
            index++;
            //leggo char per char dal file
            fscanf(fileIDread, "%c", &testoChiaro[index]);
        }
        //chiudo il file una volta finita la lettura
        fclose(fileIDread);

        index--;


        //definisco una nuova stringa della lungezza precisa
        char testoCroppato[index + 3];

        //prepongo alla stringa i valori per la codifica hash scelta
        testoCroppato[0] = '$';
        testoCroppato[1] = '5';
        testoCroppato[2] = '$';

        //itero tutte e due le stringhe copiando la stringa dopo i valori di hash
        for (int i = 0; i < index; i++) {
            testoCroppato[i + 3] = testoChiaro[i];
        }

        //carattere terminatore della stringa
        testoCroppato[index + 3] = '\0';
        printf("Testo di %d caratteri: %s \n", index, testoCroppato);

        //richiamo la funzione di hash e la stringa che conterrà la stringa generata
        char *hash = crypt(passphrase, testoCroppato);
        //testoCroppato[index + 3] = '-';
        printf("Testo hashato: %s \n", hash);

        //riapro il file in scrittura
        fileIDwrite = fopen(nomeFile, "w");
        //controllo se si sia aperto correttamente
        if (fileIDwrite != NULL) {
            //lo itero
            for (int i = 0; hash[i] != NULL; i++) {
                //scrivo char per char sul file la stringa hashata
                fprintf(fileIDread, "%c", hash[i]);
            }
        } else {
            //errore in caso il file non si apra in scrittura
            perror("Il file non si apre in scrittura /n");
        }
        //chiuso la stream di scrittura
        fclose(fileIDwrite);

    } else {
        //errore per il quale non si apre in scrittura
        perror("Puntatore nullo \n");
    }
    //divisore visuale per separare le iterazioni dei file
    printf("--------------------------------- \n");
}

int main() {

    int numeroFile;

    //cambio subito la cartella di lavoro in quella contenente i file
    if (chdir("obj") == 0) {
        printf("Sistema di criptazione multipla \n");
        printf("Inserisca il numero di file che andrà ad inserire: \n");
        //acuisisco quanti file vuole aggiungere a mano l'utente
        scanf("%d", &numeroFile);
        //richiamo la funzione di creazione file tante volte quanti file vogliamo istanziare
        for (int i = 0; i < numeroFile; i++) {
            fileCreator();
        }
        //tempo di wait per permettere un monitoring più accurato
        sleep(2.0);

        //ricontrollo il numero di file in caso ce ne siano alcuni aggiunti in altri modi
        numeroFile = fileCounter();

        printf("File da criptare: %d \n", numeroFile);

        //istanzio l'array di puntatori per i nomi dei file per poi visualizzarli
        char *fileArray[numeroFile];
        //listo i file nell'array sopra istanziato
        fileLister(fileArray);

        //itero l'array per visualizzare tutti i file della cartella
        for (int i = 0; i < numeroFile; i++) {
            //stampo i nomi dei file
            printf("File %d denominato: %s \n", i + 1, fileArray[i]);
        }
        //separatore visuale per un terminale più pulito
        printf("--------------------------------- \n");

        //funzione di cripting su tutti i file
        fileScroller();

    } else {
        //errore in cui la cartella dei file obiettivo non si apra
        perror("Cartella di lavoro non accessibile \n");
    }
    //ritorno indietro alla cartella originaria
    chdir("..");

    return 0;
}

//Test per verificare la directory di lavoro
/*
 char cwd[PATH_MAX];
if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("Current working dir: %s\n", cwd);
} else {
    perror("getcwd() error");
}
*/
