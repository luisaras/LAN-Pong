#ifndef SERVER
#define SERVER

#include "game.h"
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <iostream>

// 0 = esperando segundo cliente
// 1 = jogando
struct ServerMessage {
    int serverState;
    GameState gameState;
};

class Server : QObject {
    public:
        Server();
        ~Server();
        void run();

    public slots:
        void acceptConnection();
        void receiveAction1();
        void receiveAction2();

    private:
        QTcpServer serverSocket;
        QTcpSocket* client1;
        QTcpSocket* client2;
        Game game;
        void waitForPlayer1();
        void waitForPlayer2();
        void startGame();
        void sendGameState();
        void sendWaitingMessage(QTcpSocket*);
        void sendFullMessage(QTcpSocket*);
        bool checkConnections();
        bool isConnected(QTcpSocket*);
};

#endif
