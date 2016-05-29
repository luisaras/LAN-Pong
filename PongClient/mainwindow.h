#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
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
    ~MainWindow();

public slots:
    void connect();

private:
    QTcpSocket socket;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
