#ifndef HTTP_TIME
#define HTTP_TIME

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define GMT_EPOCH 1900
#define HTTP_DATE_LEN 100

char* currentTimeFormatted(time_t rawtime);

#endif
