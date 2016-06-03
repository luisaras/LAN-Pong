#include "mainwindow.h"
#include "ui_mainwindow.h"

#define barWidth 20
#define barHeight 80
#define ballSize 20
#define framerate 30

#define portnum 12345

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->connectButton, SIGNAL(released()), this, SLOT(connectToServer()) );

    showConnectScreen();
    server = new QTcpSocket(this);

    connect(server, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
}


void MainWindow::connectToServer() {
    QHostAddress host("192.168.7.2");
    server->abort();
    server->connectToHost(host, portnum);
    ui->warning->show();
    ui->warning->setText("Trying to connect...");
    connectionThread = QtConcurrent::run(this, &MainWindow::tryConnection);
}

void MainWindow::tryConnection() {
    int count = 0;
    while(server->state() != QAbstractSocket::ConnectedState && count < 5) {
        count++;
        QThread::currentThread()->sleep(1);
    }
    if (server->state() != QAbstractSocket::ConnectedState) {
        ui->warning->show();
        ui->warning->setText("Unable to connect.");
    } else {
        ui->warning->setText("Connected.");
    }
}

void MainWindow::keyPressEvent(QKeyEvent* e) {
    if (e->text() == "s" || e->key() == Qt::Key_Down) { // baixo
        sendMessage(1);
    } else if (e->text() == "w" || Qt::Key_Up) { // cima
        sendMessage(-1);
    }
}

void MainWindow::sendMessage(int input) {
    PlayerAction action;
    action.input = input;
    server->write((char*)(&action), (qint64) sizeof(action));
}

void MainWindow::receiveMessage() {
    ServerMessage msg;
    server->read((char *) &msg, (qint64) sizeof(msg));

    ui->warning->show();

    if (msg.serverState == 0) { // se tá esperando outro cliente
        showWaitingScreen();
    } else if (msg.serverState == 1){ // se tá no meio do jogo
        updateGameScreen(msg.gameState);
    } else if (msg.serverState == 2) { // player desconectou
        server->close();
        showDisconnectScreen();
    } else if (msg.serverState == 3) {
        showFullScreen();
    } else {
        // Qualquer outra coisa
    }
}

void MainWindow::showWaitingScreen() {
    ui->connectButton->hide();
    ui->warning->hide();
    ui->player1->hide();
    ui->player2->hide();
    ui->points1->hide();
    ui->points2->hide();
    ui->ball->hide();

    ui->startText->show();
    ui->startText->setText("Waiting for other player...");
}

void MainWindow::showConnectScreen() {
    ui->player1->hide();
    ui->player2->hide();
    ui->points1->hide();
    ui->points2->hide();
    ui->ball->hide();
    ui->warning->hide();
    ui->startText->hide();

    ui->connectButton->show();
}

void MainWindow::showFullScreen() {
    showConnectScreen();

    ui->warning->show();
    ui->warning->setText("Full server.");
}

void MainWindow::showDisconnectScreen() {
    showConnectScreen();

    ui->warning->show();
    ui->warning->setText("Player disconnected.");
}

void MainWindow::updateGameScreen(GameState state) {
    ui->connectButton->hide();
    ui->warning->hide();

    ui->player1->show();
    ui->player2->show();
    ui->points1->show();
    ui->points2->show();
    ui->ball->show();

    ui->player1->setGeometry(state.p1.x, state.p1.y, barWidth, barHeight);
    ui->player2->setGeometry(state.p2.x, state.p2.y, barWidth, barHeight);
    ui->points1->setText(QString::number(state.p1.points));
    ui->points2->setText(QString::number(state.p2.points));
    ui->ball->setGeometry(state.ballX, state.ballY, ballSize, ballSize);

    if (state.startCount > 0) {
        QString n = QString::number(std::ceil(state.startCount / framerate) + 1);
        ui->startText->show();
        ui->startText->setText("Starting in... " + n);
    } else {
        ui->startText->hide();
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
