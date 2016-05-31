#include "game.h"

#define windowWidth 600
#define windowHeight 400
#define barWidth 20
#define barHeight 80
#define barSpeed 4
#define ballSize 20
#define ballSpeed 20

using namespace std;

/*char pixels[windowWidth / 20][windowHeight / 20];

void print() {
    system("cls");
    for(int j = 0; j < windowHeight / 20; j++) {
        for(int i = 0; i < windowWidth / 20; i++) {
            cout << pixels[i][j];
        }
        cout << endl;
    }
}

void storePixels(GameState game) {
    for(int i = 0; i < windowWidth / 20; i++) {
        for(int j = 0; j < windowHeight / 20; j++) {
            //cout << i << " " << j << endl;
            pixels[i][j] = '-';
        }
    }
    for(int i = 0; i < barWidth / 20; i++) {
        for(int j = 0; j < barHeight / 20; j++) {
            pixels[game.p1.x / 20 + i][game.p1.y / 20 + j] = 'x';
            pixels[game.p2.x / 20 + i][game.p2.y / 20 + j] = 'x';
        }
    }
    for(int i = 0; i < ballSize / 20; i++) {
        for(int j = 0; j < ballSize / 20; j++) {
            pixels[(int)round(game.ballX / 20) + i][(int)round(game.ballY / 20) + j] = 'o';
        }
    }
}

int main() {
    Game game;
    while(1) {
        //cout << "frame" << endl;
        game.update();
        storePixels(game.getState());
        print();
        Sleep(1000);
    }
}*/

Game::Game() {
    srand((int) time(NULL));
    resetRound();
    players[0].points = players[1].points = 0;
    startCount = 3;
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

    if (ball.x <= 1) {
        resetRound();
        players[1].points++;
    } else if (ball.x >= windowWidth - ballSize - 1) {
        resetRound();
        players[0].points++;
    } else if (ball.y <= 1) {
        ball.dy *= -1;
    } else if (ball.y >= windowHeight - ballSize - 1) {
        ball.dy *= -1;
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
        ball.dx = ballSpeed;
    } else {
        ball.dx = -ballSpeed;
    }
    if (rand() % 2) {
        ball.dy = ballSpeed;
    } else {
        ball.dy = -ballSpeed;
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
