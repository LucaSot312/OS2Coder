#include "library.h"


int fileCounter(char nomeCartella[]) {

    //funzione che si occupa, dato in input il nome di una cartella, di esplorarla e restituire il numero di file
    //al suo interno

    int numeroFile = 0;
    DIR *dirp;
    struct dirent *entry;

    dirp = opendir(nomeCartella);
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

void fileScroller(char *nomeCartella[], int numeroFile) {

    //questa funzione scorrendo tra i file già contati di una cartella e associa il nome di ognuno di essi
    //ad un puntatore di un array di puntatori in modo così da poter richiamare quando si vuole il file tramite il suo
    //nome in ognuna altra funzione del programma.

    int indiceScroll = 0;
    int indiceArray = 0;
    DIR *dp;
    struct dirent *ep;

    dp = opendir("obj");
    if (dp != NULL) {
        while (ep = readdir(dp)) {

            if (indiceScroll == 2 || indiceScroll == 3) {
                indiceScroll++;
            } else {
                printf("File: %s \n", ep->d_name);
                nomeCartella[indiceArray] = ep->d_name;
                indiceScroll++;
                indiceArray++;
            }

        }
        closedir(dp);
    } else {
        perror("Non ho potuto aprire la cartella");
    }
}

void hashEncoder(char *nomeFile[], char passphrase[]) {
    char testoChiaro[30];
    int index = 0;
    char cwd[PATH_MAX];

    if (chdir("obj") == 0) {

        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("Current working dir: %s\n", cwd);
        } else {
            perror("getcwd() error");
        }
        printf("File %d:%s-pw:%s \n", index + 1, nomeFile,passphrase);
/*
        FILE *fileIDread = fopen(nomeFile, "r");
        if (fileIDread != NULL) {

            printf("File %s aperto per la lettura \n", nomeFile);
            fscanf(fileIDread, "%c", &testoChiaro[index]);
            while (feof(fileIDread) != 1) {
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

            /*
            FILE *fileIDwrite = fopen(nomeFile, "w");
            if (fileIDwrite != NULL) {
                //printf("File %s aperto per la scrittura \n", nomeFile);
                for (int i = 0; i < index; i++) {
                    fprintf(fileIDread, "%c", testoCriptato[i]);
                }
                fclose(fileIDwrite);

            } else {
                perror("Il file non si apre in scrittura /n");
                fclose(fileIDwrite);
            }

    } else {
        perror("Il file non si apre in lettura vecio \n");
        fclose(fileIDread);
    }
    */
        closedir("obj");
    } else {
        perror("Cartella obiettivo non aperta!!");
    }
}

int main() {

    srand(time(NULL));
    int numeroFile;
    char passfrase[] = {"pucci"};

    printf("Sistema di criptazione multipla \n");

    printf("Sto calcolando il numero di file nella cartella obiettivo \n");
    numeroFile = fileCounter("obj");
    printf("File da criptare: %d \n", numeroFile);

    char *fileArray[numeroFile];

    fileScroller(fileArray, numeroFile);

    for (int i = 0; i < numeroFile; i++) {
        printf("File %d denominato: %s \n", i + 1, fileArray[i]);
    }
    printf("--------------------------------- \n");
    printf("Proseguo con la criptazione \n");

    sleep(2.0);

    for (int i = 0; i < numeroFile; i++) {
        hashEncoder(fileArray[i], passfrase);
        sleep(1.0);
    }
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
