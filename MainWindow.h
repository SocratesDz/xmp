#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "AudioPlayer.h"
#include "Library.h"
#include "PlayListModel.h"
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
    void onDoubleClickToMusic(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    AudioPlayer* player;
    Library* library;
    PlayList* playListView;
    PlaylistModel* playListModel;
    QMediaPlaylist* playList;
};

#endif // MAINWINDOW_H
