#include "mainwindow.h"
#include "ui_mainwindow.h"

#define barWidth 20
#define barHeight 80
#define ballSize 20
#define framerate 30

#define portnum 80

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->connectButton, SIGNAL(released()), this, SLOT(connectToServer()) );
    showConnectScreen();

    //run();
}

void MainWindow::run() {
    while(1) {
        receiveMessages();
    }
}

void MainWindow::connectToServer() {
    // TODO: conectar ao socket
}

void MainWindow::keyPressEvent(QKeyEvent* e) {
    if (e->key() == Qt::Key_Up) { // baixo
        sendMessage(1);
    } else if (e->key() == Qt::Key_Down) { // cima
        sendMessage(-1);
    }
}

void MainWindow::sendMessage(int input) {
    PlayerAction action;
    action.input = input;

    // TODO: mandar mensagem por socket por servidor
}

void MainWindow::receiveMessages() {
    ServerMessage msg;

    // TODO: receber por socket

    if (msg.serverState == 0) { // se tá esperando outro cliente
        showWaitingScreen();
    } else if (msg.serverState == 1){ // se tá no meio do jogo
        updateGameScreen(msg.gameState);
    } else { // tá cheio
        showConnectScreen();
        ui->fullWarning->show();
    }
}

void MainWindow::showWaitingScreen() {
    ui->connectButton->hide();
    ui->fullWarning->hide();
    ui->player1->hide();
    ui->player2->hide();
    ui->ball->hide();

    ui->startText->show();
    ui->startText->setText("Waiting for other player...");
}

void MainWindow::showConnectScreen() {
    ui->player1->hide();
    ui->player2->hide();
    ui->ball->hide();
    ui->fullWarning->hide();
    ui->startText->hide();

    ui->connectButton->show();
}

void MainWindow::updateGameScreen(GameState state) {
    ui->connectButton->hide();
    ui->fullWarning->hide();

    ui->player1->show();
    ui->player2->show();
    ui->ball->show();

    ui->player1->setGeometry(state.p1.x, state.p1.y, barWidth, barHeight);
    ui->player2->setGeometry(state.p2.x, state.p2.y, barWidth, barHeight);
    ui->ball->setGeometry(state.ballX, state.ballY, ballSize, ballSize);

    if (state.startCount > 0) {
        QString n = QString::number(std::ceil(state.startCount / framerate));
        ui->startText->setText("Starting in... " + n);
    } else {
        ui->startText->hide();
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
