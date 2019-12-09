#include "mal.h"

void *server_reader(void *argsp)
{
    server_reader_ *args = argsp;
    int socket = args->socket;

    while (1) {
        char *buffer = malloc(BUFF_SIZE);

        recv(socket, buffer, BUFF_SIZE, 0);
        printf("[%s]\n", buffer);
    }
}

int handle_conn(int socket)
{
    server_reader_ *args = malloc(sizeof(server_reader_ *));
    args->socket = socket;
    
    pthread_t reader_id;
    pthread_create(&reader_id, NULL, server_reader, args);

    return 0;
}

int run_server()
{
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(
      server_socket,
      (struct sockaddr *) &server_address,
      sizeof(server_address)
    );

    int client_count = 0;

    printf("awaiting connections\n");
    int status = listen(server_socket, MAX_CONN);
    if (status != 0) {
        printf("error listening on socket.");
        return status;
    }

    while (client_count < MAX_CONN) {
        int accepted_socket = accept(server_socket, NULL, NULL);

        if (accepted_socket == -1) {
            printf("unable to accept client\n");
            return accepted_socket;
        }

        handle_conn(accepted_socket);
    }

    close(server_socket);

    return 0;
}