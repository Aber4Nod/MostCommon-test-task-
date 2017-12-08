#ifndef DEPS_H
#define DEPS_H

#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <regex.h>
#include <unistd.h>
#include "queue/src/pbl.h"

#define ERROR_INTERNAL 001

#define ERROR_ARG_NUMBER 101
#define ERROR_ARG_PATH 102
#define ERROR_ARG_NCORES 103

#define ERROR_SUCCESS 501
#define ERROR_EMPTY_FILE 502

/* Structure with static params */
typedef struct _Static {
    int maxlength;          // length of the longest line in the file
    int numlines;           // the total number of lines
    pthread_mutex_t lock;   // mutex
    FILE* fp;               // proceeding file stream
    char* sname;            // proceeding file path
} Static;

/* Structure with varying params */
typedef struct _Args {
    int chLeft;             // left interval border (considering a certain mergesort
                            // step) [in terms of symbols]
    int l;                  // left interval border [in terms of lines]
    int r;                  // rigth interval border [in terms of lines]
    int crNumber;           // number of threads remaining for the certain tree branch
    Static* st;
} Args;

void buildQueue(const Static* st);  // proceeding priority interval function
void MergeSort(Args* args);         // MergeSort function

#endif

