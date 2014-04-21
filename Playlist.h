#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <QStandardItemModel>
#include <QTableView>
#include <QListView>
#include <QWidget>

namespace Ui {
class PlayList;
}

class PlayList : public QWidget
{
    Q_OBJECT

public:
    explicit PlayList(QWidget *parent = 0);
    ~PlayList();
    QTableView* getTableView();
    QListView* getListView();

private:
    Ui::PlayList *ui;
    QStandardItemModel* model;
};

#endif // PLAYLIST_H
