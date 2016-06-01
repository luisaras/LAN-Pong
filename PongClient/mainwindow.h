#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QKeyEvent>
#include <QThread>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <cmath>
#include <iostream>

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
    void receiveMessage();

private:
    QFuture<void> connectionThread;
    QTcpSocket* server;
    void sendMessage(int);
    void showConnectScreen();
    void showDisconnectScreen();
    void showWaitingScreen();
    void updateGameScreen(GameState);
    void tryConnection();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
