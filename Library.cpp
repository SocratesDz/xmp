#include "Library.h"
#include "ui_Library.h"
#include <iostream>
#include "MainWindow.h"

Library::Library(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Library)
{
    ui->setupUi(this);
    model = new QFileSystemModel();
    model->setReadOnly(true);
}

Library::~Library()
{
    delete ui;
    delete model;
}

void Library::selectFolder() {
    QString folderName = QFileDialog::getExistingDirectory(this, tr("Select a music folder"));
    if(folderName.isEmpty()) return;
    std::cout << folderName.toStdString() << std::endl;
    ui->treeView->setModel(model);
    model->setRootPath(folderName);

    QModelIndex index = model->index(folderName);
    ui->treeView->expand(index);
    ui->treeView->scrollTo(index);
    ui->treeView->resizeColumnToContents(0);
    ui->treeView->setRootIndex(index);
}

QTreeView* Library::getTreeView() {
    return ui->treeView;
}
