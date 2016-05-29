#include "server.h"
#define framerate 30
#define portnum 80
using namespace std;

Server::Server() {
    QHostAddress host("192.168.7.1");

    if (!serverSocket.listen(host, portnum)) {
        std::cout << "Listen error" << std::endl;
        return;
    }

    connect(&serverSocket, SIGNAL(newConnection()),
        this, SLOT(acceptConnection()));
}

void Server::run() {
    while(1) {
        waitForPlayer1();
        waitForPlayer2();
        startGame();
    }
}

void Server::startGame() {
    game = Game();
    while(1) {
        if (!checkConnections()) {
            break;
        }
        game.update();
        QThread::currentThread()->sleep(1000 / framerate);
        sendGameState();
    }
}


bool Server::checkConnections() {
    if (isConnected(client1)) {
        if (isConnected(client2)) {
            sendWaitingMessage(client2);
        }
        return false;
    } else {
        if (isConnected(client2)) {
            sendWaitingMessage(client1);
            return false;
        }
    }
    return true;
}

void Server::sendWaitingMessage(QTcpSocket* client) {
    ServerMessage msg;
    msg.serverState = 0; // esperando outro jogador

    char* data = (char*) &msg;
    qint64 len = sizeof(msg);
    client->write(data, len);
}

void Server::sendFullMessage(QTcpSocket* client) {
    ServerMessage msg;
    msg.serverState = -1; // sala cheia
    char* data = (char*) &msg;
    qint64 len = sizeof(msg);
    client->write(data, len);
}

void Server::acceptConnection() {
    if (client1 == NULL) {
        client1 = serverSocket.nextPendingConnection();
        connect(client1, SIGNAL(readyRead()), this, SLOT(receiveAction1()));
    } else if (client2 == NULL) {
        client2 = serverSocket.nextPendingConnection();
        connect(client2, SIGNAL(readyRead()), this, SLOT(receiveAction2()));
    } else {
        QTcpSocket* client = serverSocket.nextPendingConnection();
        sendFullMessage(client);
    }
}

void Server::waitForPlayer1() {
    while(isConnected(client1)) {
        QThread::currentThread()->sleep(1);
    }
}

void Server::waitForPlayer2() {
    while(!isConnected(client2)) {
        QThread::currentThread()->sleep(1);
    }
}

void Server::sendGameState() {
    ServerMessage msg;
    msg.gameState = game.getState();
    msg.serverState = 1; // jogando

    qint64 len = sizeof(msg);
    char* data = (char*) &msg;
    client1->write(data, len);
    client2->write(data, len);
}

void Server::receiveAction1() {
    PlayerAction action;
    client1->read((char *) &action, (qint64) sizeof(action));
    action.playerID = 1;
    game.onPlayerAction(action);
}

void Server::receiveAction2() {
    PlayerAction action;
    client2->read((char *) &action, (qint64) sizeof(action));
    action.playerID = 2;
    game.onPlayerAction(action);
}

bool Server::isConnected(QTcpSocket* client) {
    if (client == NULL)
        return false;
    return client->state() == QAbstractSocket::ConnectedState;
}

Server::~Server() { }
