#include "Game.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <cmath>

#define windowWidth 600
#define windowHeight 400
#define barWidth 20
#define barHeight 80
#define barSpeed 4
#define ballSize 20
#define ballSpeed 2

using namespace std;

Game::Game() {
    srand(time(NULL));
    resetRound();
    players[0].points = players[1].points = 0;
}

void Game::run() {

    // TODO: criar threads para receber as mensagens do socket

    while(1) {
        switch (currentState) {
        case waitingPlayer1:
            // checar se alguém se conectou: se sim, passa pro waitingPlayer2
        case waitingPlayer2:
            // checar se alguém se conectou: se sim, passa pro running
        case running:
            updateBallMovement();
        }
        sendState();
        this_thread::sleep_for(24);
    }
}

void Game::updateBallMovement() {
    // TODO: fazer os cálculo louco de colisão da bola com a parede
    ball.x += ball.dx;
    ball.y += ball.dy;

    if (ball.x <= 0) {
        resetRound();
        players[1].points++;
    } else if (ball.x >= windowWidth - ballSize) {
        resetRound();
        players[0].points++;
    }

    if (ball.y <= 0) {
        // bla
    } else if (ball.y >= windowHeight - ballSize) {
        // bla
    }
}

void Game::resetRound() {
    // Posição inicial dos players
    players[0].x = 0;
    players[1].x = windowWidth - barWidth;
    players[0].y = players[1].y = (windowHeight - barHeight) / 2;

    // Posição inicial da bola
    ball.x = (windowWidth - ballSize) / 2;
    ball.y = (windowHeight - ballSize) / 2;

    // Velocidade inicial da bola
    if (rand() % 2) {
        ball.dx = ballSpeed / sqrt(2);
    } else {
        ball.dx = -ballSpeed / sqrt(2);
    }
    if (rand() % 2) {
        ball.dy = ballSpeed / sqrt(2);
    } else {
        ball.dy = -ballSpeed / sqrt(2);
    }
}

void Game::sendState() {
    RoundState state;
    state.ballX = ball.x;
    state.ballY = ball.y;
    state.p1 = players[0];
    state.p2 = players[1];
    state.isRunning = (currentState == running);

    // TODO: enviar para ambos os clientes o estado atual
}

// O que fazer com a informação que o cliente mandou
void Game::onPlayerAction(PlayerAction action) {
    if (action.input > 0) {
        players[action.playerID].y = min(players[action.playerID].y + barSpeed, windowHeight - 1);
    } else {
        players[action.playerID].y = max(players[action.playerID].y - barSpeed, 0);
    }
}
