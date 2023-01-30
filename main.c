#include "library.h"

typedef struct lista {
    char nome[10];
    int *next;
};

int fileCounter() {

    //funzione che si occupa, dato in input il nome di una cartella, di esplorarla e restituire il numero di file
    //al suo interno

    int numeroFile = 0;
    DIR *dirp;
    struct dirent *entry;

    dirp = opendir(".");
    if (dirp == NULL) {
        perror("Cartella non aperta");
    } else {
        while ((entry = readdir(dirp)) != NULL) {
            if (entry->d_type == DT_REG) {
                numeroFile++;
            }
        }
        closedir(dirp);
    }

    return numeroFile;
}

void fileScroller(char *nomeCartella[]) {

    //questa funzione scorrendo tra i file già contati di una cartella e associa il nome di ognuno di essi
    //ad un puntatore di un array di puntatori in modo così da poter richiamare quando si vuole il file tramite il suo
    //nome in ognuna altra funzione del programma.

    int indiceScroll = 0;
    int indiceArray = 0;
    DIR *dp;
    struct dirent *ep;

    dp = opendir(".");
    if (dp != NULL) {
        while ((ep = readdir(dp)) != NULL) {
            if (ep->d_type == DT_REG && strcmp(ep->d_name,".")!=0 && strcmp(ep->d_name,"..")!=0) {
                nomeCartella[indiceArray] = ep->d_name;
                indiceArray++;
            }
        }
        closedir(dp);
    } else {
        perror("Non ho potuto aprire la cartella");
    }
}

void hashEncoder(char nomeFile[]) {

    char testoChiaro[30];
    int index = 0;
    const char passphrase[] = {"pucci"};
    FILE *fileIDread;
    FILE *fileIDwrite;

    fileIDread = fopen(nomeFile, "r");
    if (fileIDread) {

        printf("Puntatore buono \n");
        fscanf(fileIDread, "%c", &testoChiaro[index]);
        while (!feof(fileIDread)) {
            index++;
            fscanf(fileIDread, "%c", &testoChiaro[index]);
        }
        fclose(fileIDread);

    } else {
        perror("Puntatore nullo \n");

    }
    /*
    if (fileIDread != NULL) {

        fscanf(fileIDread, "%c", &testoChiaro[index]);
        while (!feof(fileIDread)) {
            index++;
            fscanf(fileIDread, "%c", &testoChiaro[index]);
        }
        fclose(fileIDread);

        index--;

        char testoCriptato[index + 3];
        testoCriptato[0] = '$';
        testoCriptato[1] = '5';
        testoCriptato[2] = '$';
        for (int i = 0; i < index; i++) {
            testoCriptato[i + 3] = testoChiaro[i];
        }
        testoCriptato[index + 3] = '\0';

        printf("Testo normale: %s \n", testoChiaro);
        printf("Testo inquadrato: %s \n", testoCriptato);
        //char *hash = crypt(passphrase,testoCriptato);
        //printf("Il file %s è stato hashato in: %s \n",nomeFile,hash);
        //printf("Testo croppato: %s \n", testoCriptato);
        //printf("Lunghezza della parola: %d \n", index);


        FfileIDwrite = fopen(nomeFile, "w");
        if (fileIDwrite != NULL) {
            //printf("File %s aperto per la scrittura \n", nomeFile);
            for (int i = 0; i < index; i++) {
                fprintf(fileIDread, "%c", testoCriptato[i]);
            }
        } else {
            perror("Il file non si apre in scrittura /n");
            fclose(fileIDwrite);
        }

    fclose(fileIDwrite);
} else {
    perror("Il file non si apre in lettura vecio \n");
    fclose(fileIDread);
}
*/
    printf("--------------------------------- \n");
}

int main() {

    srand(time(NULL));
    int numeroFile;

    if (chdir("obj") == 0) {
        printf("Sistema di criptazione multipla \n");
        printf("Sto calcolando il numero di file nella cartella obiettivo \n");

        numeroFile = fileCounter();

        printf("File da criptare: %d \n", numeroFile);

        char *fileArray[numeroFile];


        fileScroller(fileArray);

        for (int i = 0; i < numeroFile; i++) {
            printf("File %d denominato: %s \n", i + 1, fileArray[i]);
        }
        printf("--------------------------------- \n");
        printf("Proseguo con la criptazione \n");

        sleep(2.0);


        for (int i = 0; i < numeroFile; i++) {
            int entryLeng = sizeof(fileArray[i]);
            char *entry[entryLeng];
            memmove(entry, fileArray[i], entryLeng);
            printf("File:%s \n", entry);
            hashEncoder(entry);
            sleep(2.0);

        }
    } else {
        perror("Cartella di lavoro non accessibile \n");
    }
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
