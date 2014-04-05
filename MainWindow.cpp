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
    player = new AudioPlayer();
    ui->playerLayout->addWidget(player); // Se agrega el widget a la ventana principal
    player->show(); // Se muestra el widget

    // Se conecta la acción del menú File->Open con la función open de AudioPlayer
    connect(ui->actionOpen, SIGNAL(triggered()), player, SLOT(open()));
}

MainWindow::~MainWindow()
{
    delete player;
    delete ui;
}
