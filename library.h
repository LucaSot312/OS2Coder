#ifndef OS2CODER_LIBRARY_H
#define OS2CODER_LIBRARY_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include "crypt.h"

int fileCounter(void);

void hashEncoder(char*);

void fileCreator(void);

void fileScroller(void);

void fileLister(char**);

#endif //OS2CODER_LIBRARY_H
