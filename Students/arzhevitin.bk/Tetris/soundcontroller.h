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
    enum Music { Title, GameProcess, Final, Records };

private:
    const QMap<Sound, QString> SOUNDS_URL = {
        { Sound::BlockFix    , "" },
        { Sound::LineClean   , "" },
        { Sound::BlockRotate , "" },
    };
    const QMap<Music, QString> MUSIC_URL = {
        { Music::Title       , "/misic/title.mp3"        },
        { Music::GameProcess , "/misic/game-process.mp3" },
        { Music::Final       , "/misic/game-over.mp3"    },
        { Music::Records     , "/misic/records.mp3"      },
    };

public slots:
    ///Воспроизводит музыку, циклично, если не наcтроено иначе
    void playMusic(Music type);
    void stopMusic();
    void pauseMusic();
    void playCurrentMusic();
    ///Проигрывает звук поверх музыки, если та вопросизводится
    void playSound(Sound type);
    void setLoopMode(bool );

private:
    QMediaPlayer    m_palyer;
    bool            m_enableLoop;
};
