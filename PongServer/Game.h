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

struct RoundState {
    bool isRunning;
    float ballX;
    float ballY;
    Player p1;
    Player p2;
};

enum GameState {
    waitingPlayer1, waitingPlayer2, running
};

class Game {
    public:
        Game();
        ~Game();
        void run();

    private:
        GameState currentState;
        Player players[2];
        Ball ball;

        // Bagulho do jogo
        void updateBallMovement();
        void resetRound();

        // Bagulho dos socket
        void onPlayerAction(PlayerAction);
        void sendState();
};
