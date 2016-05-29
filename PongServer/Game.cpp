#include "game.h"

#define windowWidth 600
#define windowHeight 400
#define barWidth 20
#define barHeight 80
#define barSpeed 4
#define ballSize 20
#define ballSpeed 2

using namespace std;

Game::Game() {

    srand((int) time(NULL));
    resetRound();
    players[0].points = players[1].points = 0;
    startCount = 120;
}

Game::~Game() { }

void Game::update() {
    if (startCount > 0) {
        startCount--;
    } else {
        moveBall();
    }
}

void Game::moveBall() {

    ball.x += ball.dx;
    ball.y += ball.dy;

    if (ball.x <= 0) {
        resetRound();
        players[1].points++;
    } else if (ball.x >= windowWidth - ballSize) {
        resetRound();
        players[0].points++;
    } else if (ball.y <= 0) {
        // TODO: fazer os cálculo louco de colisão da bola com a parede
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
        ball.dx = ballSpeed / (float)sqrt(2);
    } else {
        ball.dx = -ballSpeed / (float)sqrt(2);
    }
    if (rand() % 2) {
        ball.dy = ballSpeed / (float)sqrt(2);
    } else {
        ball.dy = -ballSpeed / (float)sqrt(2);
    }
}

GameState Game::getState() {
    GameState state;
    state.ballX = ball.x;
    state.ballY = ball.y;
    state.p1 = players[0];
    state.p2 = players[1];
    state.startCount = startCount;
    return state;
}

void Game::onPlayerAction(PlayerAction action) {
    int i = action.playerID - 1;
    if (action.input > 0) {
        players[i].y = min(players[i].y + barSpeed, windowHeight - 1);
    } else {
        players[i].y = max(players[i].y - barSpeed, 0);
    }
}
