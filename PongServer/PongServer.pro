#-------------------------------------------------
#
# Project created by QtCreator 2016-05-29T17:29:00
#
#-------------------------------------------------

QT       += core gui
QT      += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PongServer
TEMPLATE = app


SOURCES += main.cpp\
    game.cpp \
    server.cpp

HEADERS  += \
    server.h \
    game.h

FORMS    += mainwindow.ui
