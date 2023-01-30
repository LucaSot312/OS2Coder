#ifndef OS2CODER_LIBRARY_H
#define OS2CODER_LIBRARY_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include "crypt.h"

int fileCounter(char *);


void hashEncoder(char *, char *);


void fileScroller(char **, int);

#endif //OS2CODER_LIBRARY_H
