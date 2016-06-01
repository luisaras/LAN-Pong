#ifndef SERVER
#define SERVER

#include "game.h"
#include <cstdlib>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <iostream>
#include <chrono>
#include <errno.h>
#include <cstring>

// 0 = esperando segundo cliente
// 1 = jogando
struct ServerMessage {
    int serverState;
    GameState gameState;
};

class Server {

    public:
        Server();
        ~Server();
        void run();

    private:
        int socketID;
        void waitForPlayers(int&, int&);
        void startGame(int, int);
        void sendGameState(int &, int &, Game*);
        int sendWaitingMessage(int);
        int sendDisconnectMessage(int);
        bool checkConnections(int&, int&);
};

#endif
