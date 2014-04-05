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
    ui->setupUi(this);
    player = new AudioPlayer();
    connect(player->getBackendPlayer(), SIGNAL(positionChanged(qint64)), this, SLOT(onPositionChanged(qint64)));
    connect(ui->progressSlider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));
    connect(player->getBackendPlayer(), SIGNAL(durationChanged(qint64)), this, SLOT(changeSlider(qint64)));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(player->getBackendPlayer(), SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(handleStates(QMediaPlayer::MediaStatus)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_playButton_clicked()
{
    player->play();

}

void MainWindow::on_pauseButton_clicked()
{
    player->pause();
}

void MainWindow::on_stopButton_clicked()
{
    player->stop();
}

void MainWindow::onPositionChanged(qint64 progress) {
    if (!ui->progressSlider->isSliderDown()) {
        ui->progressSlider->setValue(progress / 1000);
    }
    ui->durationLabel->setText(player->getPositionAndDurationString());
}

void MainWindow::seek(int position) {
    player->setPosition(qint64(position*1000));
}

void MainWindow::changeSlider(qint64 size) {
    ui->progressSlider->setMaximum(size/1000);
}

void MainWindow::open() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open an audio file"));
    player->setMedia(QUrl::fromLocalFile(QFileInfo(fileName).absoluteFilePath()));
    player->stop();
    player->play();
}

void MainWindow::handleStates(QMediaPlayer::MediaStatus status) {
    switch(status) {
        case QMediaPlayer::EndOfMedia:
            player->stop();
            ui->progressSlider->setValue(0);
            break;
        case QMediaPlayer::InvalidMedia:
            player->stop();
            ui->progressSlider->setValue(0);
            QMessageBox::critical(this, tr("Error: No es posible reproducir el archivo"),
                                  tr("El archivo no es reproducible por XMP"));
            break;
    }
}
