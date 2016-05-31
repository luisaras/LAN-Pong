#ifndef GAME
#define GAME

#include <ctime>
#include <cmath>
#include <random>

struct Ball {
    float dx;
    float dy;
    float x;
    float y;
};

struct Player {
    int points;
    int x;
    int y;
};

struct PlayerAction {
    int playerID;
    int input;
};

struct GameState {
    int startCount;
    float ballX;
    float ballY;
    Player p1;
    Player p2;
};

class Game {
    public:
        Game();
        ~Game();
        void update();
        void onPlayerAction(PlayerAction);
        GameState getState();

    private:
        int startCount;
        Player players[2];
        Ball ball;
        void moveBall();
        void resetRound();
};

#endif
