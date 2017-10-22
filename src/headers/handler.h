#ifndef HANDLER_THREAD
#define HANDLER_THREAD

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include "httptime.h"

#define BUFF_SIZE 1025
#define LEN_ELEMENTS 1
#define READ_ONLY "r"
#define HTTP_HEADER_LEN 1000
#define CHAR_BUFF 256

typedef struct handler_args {
    int conn;
    char * buffer;
    char * path;
} handler_args;

void sendResponse();
FILE* getRootIndex(char*);
void* threadHandler(void*);

#endif