#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "AudioPlayer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_playButton_clicked();
    void on_pauseButton_clicked();
    void on_stopButton_clicked();
    void onPositionChanged(qint64 progress);
    void seek(int position);
    void changeSlider(qint64 size);
    void open();
    void handleStates(QMediaPlayer::MediaStatus status);

private:
    Ui::MainWindow *ui;
    AudioPlayer* player;
};

#endif // MAINWINDOW_H
