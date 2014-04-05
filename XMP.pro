#-------------------------------------------------
#
# Project created by QtCreator 2014-03-09T23:43:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = XMP
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    AudioPlayer.cpp

HEADERS  += MainWindow.h \
    AudioPlayer.h

FORMS    += MainWindow.ui \
    AudioPlayer.ui
