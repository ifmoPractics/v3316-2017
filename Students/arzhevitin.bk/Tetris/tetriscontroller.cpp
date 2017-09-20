#include "tetriscontroller.h"

using namespace tetriscontroller;

TetrisController::TetrisController(TetrisModel *tetrisModel, QObject *parent)
    : QObject(parent)
    , m_tetrisModel(tetrisModel)
    , m_timer(new QTimer(this))
{
    connect(m_timer, SIGNAL(timeout()), SLOT(gameDoStep()));

    this->start();
}

void TetrisController::start()
{
    m_timer->start(STEP_DELAY);
    m_soundController.playMusic(SoundController::GameProcess);
}

void TetrisController::end()
{
    m_soundController.stopMusic();
    m_timer->stop();
    emit gameOver();
}

void TetrisController::pause()
{
    m_soundController.pauseMusic();
    m_timer->stop();
}

void TetrisController::moveItemleft()
{
    m_tetrisModel->moveActiveItemLeft();
}

void TetrisController::moveItemRight()
{
    m_tetrisModel->moveActiveItemRight();
}

void TetrisController::rotateItem()
{
    m_tetrisModel->rotateActiveItem();
}

void TetrisController::enableAccelerate(bool isAccelerate)
{
    int delay = isAccelerate ? STEP_DELAY_MAX : STEP_DELAY;
    m_timer->setInterval(delay);
    this->gameDoStep();
}

void TetrisController::gameDoStep()
{
    if (m_tetrisModel->isGameActive()) {
        m_tetrisModel->doStep();
        emit doRefresh();
    } else {
        this->end();
    }
}
