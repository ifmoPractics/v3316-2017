/* Основной модуль управления всей
 * игрой
**/

#pragma once

#include "tetrisview.h"

#include <QMainWindow>
#include <QKeyEvent>

class TetrisGame : public QMainWindow
{
    Q_OBJECT

public:
    TetrisGame(QWidget *parent = 0);
    ~TetrisGame();

private:
    TetrisView* m_tetrisView;
};

