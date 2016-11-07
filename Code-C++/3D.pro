#-------------------------------------------------
#
# Project created by QtCreator 2016-04-08T16:32:40
#
#-------------------------------------------------

QT       += core gui opengl

LIBS  += -lGL -lGLU
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3D
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myglwidget.cpp \
    model.cpp \
    graph.cpp \
    fasttrackball.cpp \
    tree.cpp

HEADERS  += mainwindow.h \
    myglwidget.h \
    model.h \
    graph.h \
    fasttrackball.h \
    tree.h

FORMS    += mainwindow.ui
