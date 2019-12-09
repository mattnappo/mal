#include "mal.h"

payload_ new_payload(int pos, int max, float *locs)
{
    payload_ payload = {
        pos, max, locs
    };

    return payload;
}

int print_payload(payload_ p)
{
    printf("[payload]\n  pos %d\n  max %d\n  locs\n", p.pos, p.max);
    for (int i = 0; i < LOCS_SIZE; i++) {
        printf("    %f\n", p.locs[i]);
    }

    return 0;
}

int run_client()
{
    char *ip = "127.0.0.1";

    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr(ip);

    int connection_status = connect(
      client_socket,
      (struct sockaddr *) &server_address,
      sizeof(server_address)
    );
    
    if (connection_status == -1) {
        printf("connection failed\n");
        return connection_status;
    }
    printf("connection established\n");

    // read thread stuff here
    
    float mlocs[] = {9.887, -3.00907};
    payload_ payload = new_payload(8, 16, mlocs);
    print_payload(payload);

    send(client_socket, (void *)payload.max, BUFF_SIZE, 0);
    // }m

    while (1) {}

    close(client_socket);

    return 0;
}