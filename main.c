#include "library.h"

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

void fileLister(char *nomeArray[]) {

    //questa funzione scorrendo tra i file già contati di una cartella e associa il nome di ognuno di essi
    //ad un puntatore di un array di puntatori in modo così da poter richiamare quando si vuole il file tramite il suo
    //nome in ognuna altra funzione del programma.

    int indiceArray = 0;
    DIR *dp;
    struct dirent *ep;

    dp = opendir(".");
    if (dp != NULL) {
        while ((ep = readdir(dp)) != NULL) {
            if (ep->d_type == DT_REG && strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0) {
                nomeArray[indiceArray] = ep->d_name;
                indiceArray++;
            }
        }
        closedir(dp);
    } else {
        perror("Non ho potuto aprire la cartella");
    }
}

void fileScroller(void) {

    //questa funzione scorrendo tra i file già contati di una cartella e associa il nome di ognuno di essi
    //ad un puntatore di un array di puntatori in modo così da poter richiamare quando si vuole il file tramite il suo
    //nome in ognuna altra funzione del programma.

    int indiceArray = 0;
    DIR *dp;
    struct dirent *ep;

    dp = opendir(".");
    if (dp != NULL) {
        while ((ep = readdir(dp)) != NULL) {
            if (ep->d_type == DT_REG && strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0) {
                hashEncoder(ep->d_name);
                indiceArray++;
                sleep(2.0);
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

        printf("File: %s \n", nomeFile);
        printf("Puntatore buono \n");
        fscanf(fileIDread, "%c", &testoChiaro[index]);
        while (!feof(fileIDread)) {
            index++;
            fscanf(fileIDread, "%c", &testoChiaro[index]);
        }
        fclose(fileIDread);
        index--;

        char testoCroppato[index + 3];
        testoCroppato[0] = '$';
        testoCroppato[1] = '5';
        testoCroppato[2] = '$';
        for (int i = 0; i < index; i++) {
            testoCroppato[i + 3] = testoChiaro[i];
        }
        testoCroppato[index + 3] = '\0';
        printf("Testo di %d caratteri: %s \n", index, testoCroppato);
        char *hash = crypt(passphrase, testoCroppato);
        //testoCroppato[index + 3] = '-';
        printf("Testo hashato: %s \n", hash);


        fileIDwrite = fopen(nomeFile, "w");
        if (fileIDwrite != NULL) {
            for (int i = 0; hash[i] != NULL; i++) {
                fprintf(fileIDread, "%c", hash[i]);
            }
        } else {
            perror("Il file non si apre in scrittura /n");
        }
        fclose(fileIDwrite);

    } else {
        perror("Puntatore nullo \n");
    }
    /*

        //
        //
        //printf("Testo croppato: %s \n", testoCriptato);
        //printf("Lunghezza della parola: %d \n", index);




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
        fileLister(fileArray);
        for (int i = 0; i < numeroFile; i++) {
            printf("File %d denominato: %s \n", i + 1, fileArray[i]);
        }
        printf("--------------------------------- \n");

        fileScroller();

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
