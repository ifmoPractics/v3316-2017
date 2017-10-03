/* Файл реализации Контроллера игры.
 * Логика управление игровым процессом
**/

#pragma once

#include <QObject>
#include <QTimer>
#include "soundcontroller.h"
#include "tetrismodel.h"
#include "tetriswindow.h"


namespace tetriscontroller {
const int STEP_DELAY = 400; // in milliseconds
const int STEP_DELAY_MAX = 60; // in milliseconds
const int STEP_DELAY_NEXT_LEVEL = 30;
const int REDRAW_TIME = 5;
}


class TetrisController : public QObject
{
    Q_OBJECT

public:
    TetrisController(QObject* parent = 0);


public slots:
    void startGameTetris();
    void saveGame();
    void loadGame();
    void records();
    void startNewgame();
    void gameOver();
    void pause();

    void moveItemleft();
    void moveItemRight();
    void rotateItem();
    void enableAccelerate(bool isAccelerate);

private slots:
    void gameDoStep();
    void redrawGameField();

private:
    bool m_isGameActive;
    void addRecord(int score, int level);


private:
    QTimer          m_gameTimer, m_redrawFieldTimer;
    TetrisModel     m_tetrisModel;
    TetrisWindow    m_tetrisWindow;
    SoundController m_soundController;
    struct Records { int s1 = 0, l1 = 0, s2 = 0, l2 = 0, s3 = 0, l3 = 0; } m_records;
};
