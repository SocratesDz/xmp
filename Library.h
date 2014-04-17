#ifndef LIBRARY_H
#define LIBRARY_H

#include <QWidget>
#include <QFileDialog>
#include <QDirModel>
#include <QFileSystemModel>
#include <QTreeView>

namespace Ui {
class Library;
}

class Library : public QWidget
{
    Q_OBJECT

public:
    explicit Library(QWidget *parent = 0);
    ~Library();
    QTreeView* getTreeView();

public slots:
    void selectFolder();

private:
    Ui::Library *ui;
    QFileSystemModel* model;

};

#endif // LIBRARY_H
