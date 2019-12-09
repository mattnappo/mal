#include "mal.h"

int main(int argc, char *args[])
{
    if (argc <= 0) {
        return -1;
    }
    
    if (strcmp(args[1], "-c")) {
        run_client();
    } else if (strcmp(args[1], "-s")) {
        run_server();
    }

    return 0;
}