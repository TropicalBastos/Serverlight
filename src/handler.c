#include "headers/handler.h"

FILE *indexPtr;

/* Get the root file to be served
based on what is set in the serverlight.conf file */

FILE * getRootIndex(char * path){

    indexPtr = fopen(path, READ_ONLY);
    if(indexPtr == 0){
        printf("Error could not load view %s \n", path);
        strerror(errno);
    }
    return indexPtr;

}

/*Response headers are prepared here*/

const char * getResponseHeader(int sz){

    time_t rawtime;
    char * date = currentTimeFormatted(rawtime);
    char* response = (char *) malloc(HTTP_HEADER_LEN);
    
    //prepare header
    sprintf(response,
    "HTTP/1.1 200 OK\n"
    "Date: %s\n"
    "Server: ServerLight\n"
    "Last-Modified: Wed, 18 Oct 2017 16:05:58 GMT\n"
    "ETag: \"56d-9989200-1132c580\"\n"
    "Content-Type: text/html\n"
    "Content-Length: %d\n"
    "Accept-Ranges: bytes\n"
    "Connection: close\n"
    "\n", date, sz);
   
    return response;
    
}

/*Send the response to the client*/

void sendResponse(int& conn, char* buffer, FILE* index){

    //measure size of file so that we can set the correct http header
    int sz;
    fseek(index, 0L, SEEK_END);
    sz = ftell(index);
    rewind(index);
    const char* res = getResponseHeader(sz);
    
    //send the http header to client
    write(conn, res, sizeof(char) * strlen(res));

    //read the file and send it to the client
    while (fread(buffer, sizeof(char *), LEN_ELEMENTS, index) 
    == LEN_ELEMENTS){
        write(conn, buffer, sizeof(buffer));
    }

    //close the file to avoid any segmentation faults
    fclose(index);

}

/* The main handler thread that sends 
a response to the client once connected */

void* threadHandler(void* args){

    handler_args* hargs = (handler_args *) args;
    char * path = hargs->path;
    hargs->buffer = (char *) malloc(BUFF_SIZE);
    sendResponse(hargs->conn, hargs->buffer, getRootIndex(path));
    close(hargs->conn);
    free(hargs);
    pthread_exit(args);

}