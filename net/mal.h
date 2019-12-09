#ifndef MAL_H
#define MAL_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

int run_server();
int run_client();

#define MAX_CONN 5
#define PORT 42001
#define BUFF_SIZE 512
#define LOCS_SIZE 2

typedef enum req_type_ {
    ACCESS,
    EXEC
} req_type_;

typedef struct loc_ {
    double x;
    double y;
    double z;
    double t;
} loc_;

typedef struct payload_ {
    unsigned int frame;
    unsigned int max;
    
    req_type_ req;
    loc_ locs[LOCS_SIZE];
    
} payload_;

typedef struct server_reader_ {
    int socket;
} server_reader_;

#endif