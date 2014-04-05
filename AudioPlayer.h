#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QtMultimedia/QMediaPlayer>
#include <QTime>

class AudioPlayer
{
    QMediaPlayer* player;
public:
    AudioPlayer();
    void play();
    void pause();
    void stop();
    void next();
    void prev();
    void setMedia(const QMediaContent& media);
    void setPlaylist(QMediaPlaylist* playlist);
    qint64 getDuration();
    QTime getPositionTime();
    QTime getDurationTime();
    QString getPositionAndDurationString();
    void setPosition(qint64 position);
    void setVolume(int volume);
    QMediaPlayer* getBackendPlayer();

    bool isPlaying();
    bool isPaused();
    bool isStopped();
};

#endif // AUDIOPLAYER_H
