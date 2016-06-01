#include "server.h"

int main(int, char**) {
    srand((int) time(NULL));

    Server server;
    server.run();

    return 0;
}
