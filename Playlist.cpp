#include "PlayList.h"
#include <QListView>
#include "ui_Playlist.h"

PlayList::PlayList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayList)
{
    ui->setupUi(this);
    model = new QStandardItemModel(1, 0, this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Título")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Intérprete colaboradores")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Duración")));
    ui->tableView->setModel(model);

}

PlayList::~PlayList()
{
    delete ui;
    delete model;
}

QTableView* PlayList::getTableView() {
    return ui->tableView;
}
