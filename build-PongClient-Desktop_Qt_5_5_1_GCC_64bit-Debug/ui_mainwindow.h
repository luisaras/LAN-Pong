/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *connectButton;
    QLabel *warning;
    QLabel *player1;
    QLabel *player2;
    QLabel *startText;
    QLabel *ball;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(600, 400);
        MainWindow->setMinimumSize(QSize(600, 400));
        MainWindow->setMaximumSize(QSize(600, 400));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        connectButton = new QPushButton(centralWidget);
        connectButton->setObjectName(QStringLiteral("connectButton"));
        connectButton->setGeometry(QRect(220, 120, 141, 61));
        QFont font;
        font.setPointSize(16);
        connectButton->setFont(font);
        warning = new QLabel(centralWidget);
        warning->setObjectName(QStringLiteral("warning"));
        warning->setGeometry(QRect(200, 190, 181, 21));
        QFont font1;
        font1.setPointSize(10);
        warning->setFont(font1);
        warning->setAlignment(Qt::AlignCenter);
        player1 = new QLabel(centralWidget);
        player1->setObjectName(QStringLiteral("player1"));
        player1->setGeometry(QRect(0, 130, 20, 80));
        player1->setStyleSheet(QLatin1String("border: 1px solid black;\n"
"background-color: red"));
        player2 = new QLabel(centralWidget);
        player2->setObjectName(QStringLiteral("player2"));
        player2->setGeometry(QRect(580, 130, 20, 80));
        player2->setStyleSheet(QLatin1String("border: 1px solid black;\n"
"background-color: blue"));
        startText = new QLabel(centralWidget);
        startText->setObjectName(QStringLiteral("startText"));
        startText->setGeometry(QRect(180, 60, 221, 31));
        QFont font2;
        font2.setPointSize(12);
        startText->setFont(font2);
        startText->setStyleSheet(QStringLiteral(""));
        startText->setLineWidth(2);
        startText->setAlignment(Qt::AlignCenter);
        ball = new QLabel(centralWidget);
        ball->setObjectName(QStringLiteral("ball"));
        ball->setGeometry(QRect(280, 220, 20, 20));
        ball->setStyleSheet(QLatin1String("border: 1px solid black;\n"
"background-color: white"));
        ball->setFrameShape(QFrame::Box);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        connectButton->setText(QApplication::translate("MainWindow", "Connect!", 0));
        warning->setText(QApplication::translate("MainWindow", "There're already two players.", 0));
        player1->setText(QString());
        player2->setText(QString());
        startText->setText(QApplication::translate("MainWindow", "Starting in...", 0));
        ball->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
