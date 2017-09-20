#include "tetrisgame.h"

TetrisGame::TetrisGame(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(500, 700);

    m_tetrisView = new TetrisView(this);
    this->setCentralWidget(m_tetrisView);

    //необходимо для того, чтобы доходили нажатия клавиш
    m_tetrisView->setFocus();

    connect(m_tetrisView, SIGNAL(gameOver()), SLOT(close()));
}

TetrisGame::~TetrisGame()
{

}
