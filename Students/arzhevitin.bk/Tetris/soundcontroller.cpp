#include "soundcontroller.h"

#include <QSound>
#include <QMediaPlaylist>
#include <QDir>

SoundController::SoundController(QObject* parent)
    : QObject(parent)
    , m_palyer(new QMediaPlayer(this))
    , m_enableLoop(true)
{
}

void SoundController::playMusic(Music type)
{
    QMediaPlaylist* playlist = new QMediaPlaylist(this);

    QString path = QDir::currentPath() + MUSIC_URL[type];
    playlist->addMedia(QUrl(MUSIC_URL[type]));
    if (m_enableLoop) {
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
    }
    m_palyer.setPlaylist(playlist);
    m_palyer.play();
}

void SoundController::stopMusic()
{
    m_palyer.stop();
    m_palyer.deleteLater();
}

void SoundController::pauseMusic()
{
    m_palyer.pause();
}

void SoundController::playSound(Sound type)
{
    QSound::play(SOUNDS_URL[type]);
}

void SoundController::setLoopMode(bool t)
{
    m_enableLoop = t;
}
