#-------------------------------------------------
#
# Project created by QtCreator 2014-03-09T23:43:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = XMP
TEMPLATE = app


SOURCES += \
    AudioPlayer.cpp \
    main.cpp \
    MainWindow.cpp \
    Library.cpp \
    Playlist.cpp \
    PlayListModel.cpp

HEADERS  += \
    AudioPlayer.h \
    MainWindow.h \
    Library.h \
    Playlist.h \
    Playlist.h \
    PlayListModel.h

FORMS    += \
    AudioPlayer.ui \
    MainWindow.ui \
    Playlist.ui \
    Library.ui
