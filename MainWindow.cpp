#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <iostream>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Crea la interfaz gráfica
    ui->setupUi(this);

    // Llamando al módulo de AudioPlayer
    player = new AudioPlayer(this);
    ui->playerLayout->addWidget(player); // Se agrega el widget a la ventana principal
    player->show(); // Se muestra el widget

    // Llamando al módulo de Librería
    library = new Library(this);
    ui->libraryLayout->addWidget(library);
    library->show();

    // Se conecta la acción del menú File->Open con la función open de AudioPlayer
    connect(ui->actionOpen, SIGNAL(triggered()), player, SLOT(open()));


    connect(ui->actionSelect_music_folder, SIGNAL(triggered()), library, SLOT(selectFolder()));

    // Reproduciendo una canción de la biblioteca cuando se de doble clic
    connect(library->getTreeView(), SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(playSongFromLibrary()));

}

MainWindow::~MainWindow()
{
    delete player;
    delete library;
    delete ui;
}

void MainWindow::playSongFromLibrary() {
    QFileSystemModel* model = (QFileSystemModel*)library->getTreeView()->model();
    QString filePath = model->filePath(library->getTreeView()->currentIndex());
    player->stop();
    player->setMedia(QUrl::fromLocalFile(filePath));
    player->play();
}
