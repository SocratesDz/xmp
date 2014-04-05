#include "AudioPlayer.h"
#include "ui_AudioPlayer.h"
#include <QMessageBox>
#include <QFileDialog>

AudioPlayer::AudioPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioPlayer)
{
    player = new QMediaPlayer();

    ui->setupUi(this);
    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    ui->prevButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    createConnections();
}

AudioPlayer::~AudioPlayer()
{
    delete ui;
}

void AudioPlayer::play() {
    if(isPlaying()) return;
    player->play();
}

void AudioPlayer::pause() {
    if(isPaused()) return;
    player->pause();
}

void AudioPlayer::stop() {
    if(isStopped()) return;
    player->stop();
}

void AudioPlayer::prev() {

}

void AudioPlayer::next() {

}

bool AudioPlayer::isPlaying() {
    return (player->state() == QMediaPlayer::PlayingState);
}

bool AudioPlayer::isPaused() {
    return (player->state() == QMediaPlayer::PausedState);
}

bool AudioPlayer::isStopped() {
    return (player->state() == QMediaPlayer::StoppedState);
}

void AudioPlayer::seek(int position) {
    player->setPosition(qint64(position*1000));
}

void AudioPlayer::handleStates(QMediaPlayer::MediaStatus status) {
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

void AudioPlayer::onPositionChanged(qint64 position) {
    if (!ui->progressSlider->isSliderDown()) {
        ui->progressSlider->setValue(position / 1000);
    }
    ui->durationLabel->setText(getPositionAndDurationString());
}

QTime AudioPlayer::getPositionTime() {
    qint64 position = player->position() / 1000; // Convert miliseconds to seconds
    return QTime((position/3600)%60, // Get the hours (from seconds)
                 (position/60)%60, // Get the minutes (from seconds)
                 (position)%60, // Get the seconds
                 (position*1000)%1000); // Get the miliseconds
}

QTime AudioPlayer::getDurationTime() {
    qint64 duration = player->duration() / 1000; // Convert miliseconds to seconds
    return QTime((duration/3600)%60, // Get the hours (from seconds)
                 (duration/60)%60,  // Get the minutes (from seconds)
                 (duration)%60, // Get the seconds
                 (duration*1000)%1000); // Get the miliseconds
}

QString AudioPlayer::getPositionAndDurationString() {
    QString stringTime;
    QTime currentTime(getPositionTime());
    QTime totalTime(getDurationTime());
    QString format = "mm:ss";

    // Si dura más de una hora, entonces cambia el formato del tiempo
    if ((getDuration()/1000) > 3600)
        format = "hh:mm:ss";

    stringTime = currentTime.toString(format) + " / " + totalTime.toString(format);
    return stringTime;
}

qint64 AudioPlayer::getDuration() {
    return player->duration();
}

void AudioPlayer::setMedia(const QMediaContent &media) {
    player->setMedia(media);
}

void AudioPlayer::setPlaylist(QMediaPlaylist *playlist) {
    this->playlist = playlist;
    player->setPlaylist(this->playlist);
}

void AudioPlayer::setPosition(qint64 position) {
    player->setPosition(position);
}

void AudioPlayer::setVolume(int volume) {
    player->setVolume(volume);
}

void AudioPlayer::open() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open an audio file"));
    if(fileName.isEmpty()) return;
    player->setMedia(QUrl::fromLocalFile(QFileInfo(fileName).absoluteFilePath()));
    player->stop();
    player->play();
}

void AudioPlayer::changeSlider(qint64 size) {
    ui->progressSlider->setMaximum(size / 1000);
}

void AudioPlayer::createConnections() {
    // Si cambia la posición del audio, se cambia el valor de la lista y se actualiza el label de la duración
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(onPositionChanged(qint64)));

    // Si se mueve el slider, se cambia la posición del audio
    connect(ui->progressSlider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));

    // Si se cambia la duración total del audio, se actualiza el slider
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(changeSlider(qint64)));

    // Si ocurre un estado en el reproductor, se maneja
    connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(handleStates(QMediaPlayer::MediaStatus)));

    // Se conectan los botones con las acciones del reproductor
    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(play()));
    connect(ui->pauseButton, SIGNAL(clicked()), this, SLOT(pause()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stop()));
    connect(ui->prevButton, SIGNAL(clicked()), this, SLOT(prev()));
    connect(ui->nextButton, SIGNAL(clicked()), this, SLOT(next()));
}
