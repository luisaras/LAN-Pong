#-------------------------------------------------
#
# Project created by QtCreator 2016-05-29T17:29:00
#
#-------------------------------------------------

QT += core
QT -= gui
LIBS += -pthread
CONFIG += c++11

TARGET = PongServer
TEMPLATE = app


SOURCES += main.cpp\
    game.cpp \
    server.cpp \

HEADERS  += \
    server.h \
    game.h \
