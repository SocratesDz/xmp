#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "AudioPlayer.h"
#include "Library.h"
#include "PlayList.h"

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
    void playSongFromLibrary();

private:
    Ui::MainWindow *ui;
    AudioPlayer* player;
    Library* library;
    PlayList* playList;
};

#endif // MAINWINDOW_H
