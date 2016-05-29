#include "Server.h"
#include <thread>
using namespace std;

Server::Server() { }

Server::~Server() { }

void Server::startGame() {

    //thread receiver(&Server::handleClients, this);

    game = Game();
    while(1) {
        if (clientID1 < 0 || clientID2 < 0) {
            break;
        }
        game.update();
        //this_thread::sleep_for(24);
        sendGameState();
    }
}

void Server::run() {
    while(1) {
        if (clientID1 < 0) {
            waitForPlayer1();
        }
        if (clientID2 < 0) {
            waitForPlayer2();
        }
        startGame();
    }
}

void Server::waitForPlayer1() {
    // usar o connect e tals do socket
}

void Server::waitForPlayer2() {
    // usar o connect e tals do socket
}

void Server::sendGameState() {
    ServerMessage msg;
    msg.gameState = game.getState();
    msg.serverState = 1; // jogando

    // TODO: enviar por socket para os dois jogadores
}

void Server::onClientDisconnect() {
    game = Game(); // resetar jogo

    ServerMessage msg;
    msg.gameState = game.getState();
    msg.serverState = 0; // esperando outro jogador

    // TODO: enviar por socket para o cliente que ainda está conectado, se tiver
}

void Server::receiveMessages() {
    while(1) {
        PlayerAction action;

        // TODO: receber as mensagens via socket
        // TODO: setar o action.playerID de acordo com o clientID

        game.onPlayerAction(action);
    }
}
