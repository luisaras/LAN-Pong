#ifndef SERVER
#define SERVER

#include "Game.h"

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
        Game game;
        int clientID1;
        int clientID2;
        void waitForPlayer1();
        void waitForPlayer2();
        void startGame();
        void receiveMessages();
        void sendGameState();
        void onClientDisconnect();
};

#endif
