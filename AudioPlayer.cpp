#include "AudioPlayer.h"
#include <QtMultimedia/QMediaPlayer>
#include <QFileInfo>
#include <QFileDialog>

AudioPlayer::AudioPlayer()
{
    player = new QMediaPlayer();
}

void AudioPlayer::play() {
    if(isPlaying()) return;
    player->setVolume(10);
    player->play();
}

bool AudioPlayer::isPlaying() {
    return (player->state() == QMediaPlayer::PlayingState);
}

void AudioPlayer::pause() {
    if(isPaused()) return;
    player->pause();
}

bool AudioPlayer::isPaused() {
    return (player->state() == QMediaPlayer::PausedState);
}

void AudioPlayer::next() {

}

void AudioPlayer::prev() {

}

void AudioPlayer::stop() {
    if(isStopped()) return;
    player->stop();
}

bool AudioPlayer::isStopped() {
    return (player->state() == QMediaPlayer::StoppedState);
}

qint64 AudioPlayer::getDuration() {
    return player->duration();
}

void AudioPlayer::setPosition(qint64 position) {
    player->setPosition(position);
}

QMediaPlayer* AudioPlayer::getBackendPlayer() {
    return player;
}


void AudioPlayer::setMedia(const QMediaContent &media) {
    player->setMedia(media);
}

void AudioPlayer::setPlaylist(QMediaPlaylist *playlist) {
    player->setPlaylist(playlist);
}

void AudioPlayer::setVolume(int volume) {
    player->setVolume(volume);
}

QTime AudioPlayer::getDurationTime() {
    return QTime((player->duration()/3600)%60,
                 (player->duration()/60)%60,
                 (player->duration())%60,
                 (player->duration()*1000)%1000);
}

QTime AudioPlayer::getPositionTime() {
    return QTime((player->position()/3600)%60,
                 (player->position()/60)%60,
                 (player->position())%60,
                 (player->position()*1000)%1000);
}

QString AudioPlayer::getPositionAndDurationString() {
    QString stringTime;
    QTime currentTime(getPositionTime());
    QTime totalTime(getDurationTime());
    QString format = "mm:ss";
    if ((getDuration()/1000) > 3600)
        format = "hh:mm:ss";
    stringTime = currentTime.toString(format) + " / " + totalTime.toString(format);
    return stringTime;
}
