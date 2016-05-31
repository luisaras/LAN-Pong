#include "server.h"
#define framerate 30
#define portnum 12345
using namespace std;

Server::Server() {

    socketID = socket(AF_INET, SOCK_STREAM, 0);

    if (socketID == -1) {
        cout << "Socket error" << endl;
    }

    sockaddr_in addr;
    bzero((char *) &addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(portnum);
    addr.sin_addr.s_addr = inet_addr("192.168.7.2");

    int bindID = bind(socketID, (sockaddr*)&addr, sizeof(addr));
    if (bindID == -1) {
        cout << "Bind error " << strerror(errno) << endl;
    }

    int listenID = listen(socketID, 10);
    if (listenID == -1) {
        cout << "Listen error" << endl;
    }
}

void Server::run() {
    int client1 = 0, client2 = 0;

    while(1) {
        cout << "Waiting for players" << endl;
        waitForPlayers(client1, client2);
        startGame(client1, client2);
    }
}

void Server::startGame(int client1, int client2) {
    Game game;
    thread receiver1(&Server::receiveActions, this, 1, &client1, &game);
    thread receiver2(&Server::receiveActions, this, 2, &client2, &game);
    cout << "Starting game..." << endl;
    while(1) {
        game.update();
        sendGameState(client1, client2, game);
        if (client1 <= 0 || client2 <= 0) {
            break;
        }
        this_thread::sleep_for(chrono::seconds(1 / framerate));
    }
    cout << "Game over." << endl;
}

int Server::sendWaitingMessage(int clientID) {
    ServerMessage msg;
    msg.serverState = 0; // esperando outro jogador

    cout << "Mandando mensagem para o cliente..." << endl;

    return recv(clientID, (char*)(&msg), sizeof(msg), 0);
}

void Server::sendGameState(int &client1, int &client2, Game &game) {
    ServerMessage msg;
    msg.gameState = game.getState();
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

void Server::receiveActions(int playerID, int* clientID, Game* game){
    while (1) {
        PlayerAction action;
        int msgID = recv(*clientID, (char*)(&action), sizeof(action), 0);
        if (msgID <= 0) {
            *clientID = -1;
            cout << "deu bosta" << endl;
            break;
        }
        cout << "recebeu mensagem" << endl;
        action.playerID = playerID;
        game->onPlayerAction(action);
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
                // Ambos os clientes estão conectados
                break;
            } else {
                // Só o client2 está conectado
                sendWaitingMessage(client2);
                client1 = accept(socketID, (sockaddr*)(&addr), &size);
                cout << "Alguém conectou com id " << client1 << endl;
            }
        } else {
            if (client1 > 0) {
                // Só o client1 está conectado
                sendWaitingMessage(client1);
                client2 = accept(socketID, (sockaddr*)(&addr), &size);
                cout << "Alguém conectou com id " << client2 << endl;
            } else {
                // Ambos estão desconectados
                client1 = accept(socketID, (sockaddr*)(&addr), &size);
                cout << "Alguém conectou com id " << client1 << endl;
            }
        }
    }

}

Server::~Server() { }
