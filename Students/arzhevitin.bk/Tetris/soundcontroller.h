#pragma once

#include <QObject>
#include <QMediaPlayer>
#include <QMap>

class SoundController : public QObject
{
    Q_OBJECT

public:
    SoundController(QObject* parent = nullptr);

    enum Sound { BlockFix, LineClean, BlockRotate };
    enum Music { Title, GameProcess, Final };

private:
    const QMap<Sound, QString> SOUNDS_URL = {
        { Sound::BlockFix    , "" },
        { Sound::LineClean   , "" },
        { Sound::BlockRotate , "" },
    };
    const QMap<Music, QString> MUSIC_URL = {
        { Music::Title       , "qrc:/misic/title.mp3"        },
        { Music::GameProcess , "qrc:/misic/game-process.mp3" },
        { Music::Final       , "qrc:/misic/game-over.mp3"    },
    };

public slots:
    ///Воспроизводит музыку, циклично, если не наcтроено иначе
    void playMusic(Music type);
    void stopMusic();
    void pauseMusic();
    ///Проигрывает звук поверх музыки, если та вопросизводится
    void playSound(Sound type);
    void setLoopMode(bool );

private:
    QMediaPlayer    m_palyer;
    bool            m_enableLoop;
};
