/* Файл реализации Контроллера игры.
 * Логика управление игровым процессом
**/

#pragma once

#include <QObject>
#include <QTimer>
#include "soundcontroller.h"
#include "tetrismodel.h"

namespace tetriscontroller {
const int STEP_DELAY = 400; // in milliseconds
const int STEP_DELAY_MAX = 60; // in milliseconds
}


class TetrisController : public QObject
{
    Q_OBJECT

public:
    TetrisController(TetrisModel *tetrisModel, QObject* parent = 0);

signals:
    void doRefresh();
    void gameOver();

public slots:
    void start();
    void end();
    void pause();

    void moveItemleft();
    void moveItemRight();
    void rotateItem();
    void enableAccelerate(bool isAccelerate);

private slots:
    void gameDoStep();

private:
    TetrisModel*    m_tetrisModel;
    QTimer*         m_timer;
    SoundController m_soundController;
};
