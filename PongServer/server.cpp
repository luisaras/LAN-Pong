#include "server.h"
#define framerate 30
#define portnum 12345
using namespace std;

void receiveActions(int playerID, int& clientID, Game* game) {
    while (clientID > 0) {
        PlayerAction action;
        int msgID = recv(clientID, (char*)(&action), sizeof(action), 0);
        if (msgID <= 0 || clientID <= 0) {
            clientID = -1;
            cout << "deu bosta" << endl;
            break;
        }
        cout << "recebeu mensagem" << endl;
        action.playerID = playerID;
        cout << game->players[0].y << " " << game->players[1].y << endl;
        game->onPlayerAction(action);
        cout << game->players[0].y << " " << game->players[1].y << endl;
    }
}

Server::Server() {

    for(int i = 0; i < maxGames; i++) {
        games[i] = NULL;
    }

    socketID = socket(AF_INET, SOCK_STREAM, 0);

    if (socketID == -1) {
        cout << "Socket error" << endl;
    }

    sockaddr_in addr;
    bzero((char *) &addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(portnum);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int bindID = bind(socketID, (sockaddr*) &addr, sizeof(addr));
    if (bindID == -1) {
        cout << "Bind error " << strerror(errno) << endl;
    }

    int listenID = listen(socketID, 10);
    if (listenID == -1) {
        cout << "Listen error" << endl;
    }
}

void Server::run() {
    int client1, client2;

    while(1) {
        client1 = client2 = -1;
        cout << "Waiting for players" << endl;
        waitForPlayers(client1, client2);
        int i = findEmptyGameSlot();
        if (i >= 0) {
            games[i] = new thread(&Server::startGame, this, i, client1, client2);
        } else {
            sendFullMessage(client1);
            sendFullMessage(client2);
        }
    }
}

void Server::startGame(int i, int client1, int client2) {
    Game *game = new Game();
    thread receiver1(receiveActions, 1, ref(client1), ref(game));
    thread receiver2(receiveActions, 2, ref(client2), ref(game));
    cout << "Starting game..." << endl;
    while(1) {
        auto then = chrono::high_resolution_clock::now();

        game->update();
        sendGameState(client1, client2, game);

        if (!checkConnections(client1, client2)) {
            break;
        }

        auto now = chrono::high_resolution_clock::now();
        auto d = now - then;
        auto time = chrono::milliseconds((long int)(1000 * 1.0 / framerate)) - d;
        this_thread::sleep_for(time);
    }
    cout << "Game over." << endl;

    receiver1.join();
    receiver2.join();

    games[i] = NULL;
}

int Server::sendWaitingMessage(int clientID) {
    ServerMessage msg;
    msg.serverState = 0; // esperando outro jogador

    return send(clientID, (char*)(&msg), sizeof(msg), 0);
}

int Server::sendDisconnectMessage(int clientID) {
    ServerMessage msg;
    msg.serverState = 2; // jogador disconectado

    return send(clientID, (char*)(&msg), sizeof(msg), 0);
}

int Server::sendFullMessage(int clientID) {
    ServerMessage msg;
    msg.serverState = 3; // server cheio

    return send(clientID, (char*)(&msg), sizeof(msg), 0);
}

void Server::sendGameState(int &client1, int &client2, Game* game) {
    ServerMessage msg;
    msg.gameState = game->getState();
    msg.serverState = 1; // jogando

    if (send(client1, (char*)(&msg), sizeof(msg), 0) <= 0) {
       // deu bosta
        client1 = -1;
        return;
    }
    if (send(client2, (char*)(&msg), sizeof(msg), 0) <= 0) {
       // deu bosta
        client2 = -1;
        return;
    }
}

void Server::waitForPlayers(int &client1, int &client2) {
    sockaddr_in addr;
    socklen_t size = sizeof(addr);

    while(1) {
        if (getsockname(client1, (struct sockaddr *)&addr, &size) == -1) {
            client1 = -1;
        }
        if (getsockname(client1, (struct sockaddr *)&addr, &size) == -1) {
            client2 = -1;
        }
        if (client2 > 0) {
            if (client1 > 0) {
                // Ambos os clientes est??o conectados
                break;
            } else {
                // S?? o client2 est?? conectado
                sendWaitingMessage(client2);
                client1 = accept(socketID, (sockaddr*)(&addr), &size);
                cout << "Algu??m conectou com id " << client1 << endl;
            }
        } else {
            if (client1 > 0) {
                // S?? o client1 est?? conectado
                sendWaitingMessage(client1);
                client2 = accept(socketID, (sockaddr*)(&addr), &size);
                cout << "Algu??m conectou com id " << client2 << endl;
            } else {
                // Ambos est??o desconectados
                client1 = accept(socketID, (sockaddr*)(&addr), &size);
                cout << "Algu??m conectou com id " << client1 << endl;
            }
        }
    }
}

bool Server::checkConnections(int &client1, int &client2) {
    if (client1 > 0) {
        if (client2 > 0) {
            return true;
        } else {
            sendDisconnectMessage(client1);
            return false;
        }
    } else {
        if (client2 > 0) {
            sendDisconnectMessage(client2);
            return false;
        } else {
            return false;
        }
    }
}

int Server::findEmptyGameSlot() {
    for(int i = 0; i < maxGames; i++) {
        if (games[i] == NULL) {
            return i;
        }
    }
    return -1;
}

Server::~Server() { }
