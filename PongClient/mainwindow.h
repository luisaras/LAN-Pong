#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QKeyEvent>
#include <cmath>

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

struct ServerMessage {
    int serverState;
    GameState gameState;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent*);
    ~MainWindow();

public slots:
    void connectToServer();

private:
    QTcpSocket socket;
    void run();
    void sendMessage(int);
    void receiveMessages();
    void showConnectScreen();
    void showWaitingScreen();
    void updateGameScreen(GameState);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
