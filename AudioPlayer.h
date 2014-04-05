#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTime>

namespace Ui {
class AudioPlayer;
}

class AudioPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit AudioPlayer(QWidget *parent = 0);
    ~AudioPlayer();
    QString getPositionAndDurationString();
    bool isPlaying();
    bool isPaused();
    bool isStopped();
    void setMedia(const QMediaContent& media);
    void setPlaylist(QMediaPlaylist* playlist);

public slots:
    void play();
    void pause();
    void stop();
    void next();
    void prev();
    void open();

private slots:
    void setPosition(qint64 position);
    void setVolume(int volume);
    void handleStates(QMediaPlayer::MediaStatus status);
    void seek(int position);
    void onPositionChanged(qint64 position);
    void changeSlider(qint64 size);

private:
    Ui::AudioPlayer *ui;
    QMediaPlayer* player;
    QMediaPlaylist* playlist;
    qint64 getDuration();
    QTime getPositionTime();
    QTime getDurationTime();
    void createConnections();
};

#endif // AUDIOPLAYER_H
