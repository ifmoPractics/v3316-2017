#include "tetriscontroller.h"

#include "savecontroller.h"
#include "algorithm"

using namespace tetriscontroller;

TetrisController::TetrisController(QObject *parent)
    : QObject(parent)
{  
    connect(&m_gameTimer, SIGNAL(timeout()), SLOT(gameDoStep()));

    connect(&m_redrawFieldTimer, SIGNAL(timeout()), SLOT(redrawGameField()));

    connect(&m_tetrisWindow, SIGNAL(on_moveLeft()), SLOT(moveItemleft()), Qt::DirectConnection);
    connect(&m_tetrisWindow, SIGNAL(on_moveRight()), SLOT(moveItemRight()), Qt::DirectConnection);
    connect(&m_tetrisWindow, SIGNAL(on_rotate()), SLOT(rotateItem()), Qt::DirectConnection);
    connect(&m_tetrisWindow, SIGNAL(on_accelerate(bool)), SLOT(enableAccelerate(bool)), Qt::DirectConnection);
    connect(&m_tetrisWindow, SIGNAL(on_keyPause()), SLOT(pause()), Qt::DirectConnection);

    connect(&m_tetrisWindow, SIGNAL(on_pushBtnNewgame()), SLOT(startNewgame()));
    connect(&m_tetrisWindow, SIGNAL(on_pushBtnContinue()), SLOT(loadGame()));
    connect(&m_tetrisWindow, SIGNAL(on_pushBtnExit()), SLOT(saveGame()));
    connect(&m_tetrisWindow, SIGNAL(on_pushBtnRecords()), SLOT(saveGame()));
    connect(&m_tetrisWindow, SIGNAL(on_pushBtnRecords()), SLOT(records()));

    connect(&m_tetrisWindow, SIGNAL(on_switchOn()), SLOT(startGameTetris()));

    SaveController::loadRecord(m_records.s1, m_records.l1
                               , m_records.s2, m_records.l2
                               , m_records.s3, m_records.l3);

    m_tetrisWindow.setRecord(m_records.s1, m_records.l1
                             , m_records.s2, m_records.l2
                             , m_records.s3, m_records.l3);

    m_tetrisWindow.show();
}

void TetrisController::startGameTetris()
{
    m_isGameActive = false;    
    m_soundController.playMusic(SoundController::Title);
}

void TetrisController::saveGame()
{
    if (m_isGameActive && m_tetrisModel.isGameActive()) {
        m_isGameActive = false;
        m_gameTimer.stop();
        m_redrawFieldTimer.stop();
        SaveController::saveGame(m_tetrisModel);
        m_soundController.playMusic(SoundController::Title);
    }
}

void TetrisController::loadGame()
{
    if (!m_isGameActive) {
        m_isGameActive = true;
        bool isOpen = SaveController::loadGame(m_tetrisModel);
        if (!isOpen) {
            startNewgame();
            return;
        }
        m_soundController.playMusic(SoundController::GameProcess);
        m_gameTimer.start(STEP_DELAY);
        m_redrawFieldTimer.start(REDRAW_TIME);
    }
}

void TetrisController::records()
{
    m_soundController.playMusic(SoundController::Records);
}

void TetrisController::startNewgame()
{
    m_tetrisModel = TetrisModel(); //Обновление состояния
    m_isGameActive = true;
    m_soundController.playMusic(SoundController::GameProcess);
    m_gameTimer.start(STEP_DELAY);
    m_redrawFieldTimer.start(REDRAW_TIME);
}

void TetrisController::gameOver()
{
    m_isGameActive = false;
    m_gameTimer.stop();
    m_redrawFieldTimer.stop();
    m_tetrisWindow.showGameover();
    m_soundController.playMusic(SoundController::Final);

    addRecord(m_tetrisModel.getScore(), m_tetrisModel.getLevel());
    SaveController::saveRecord(m_records.s1, m_records.l1
                               , m_records.s2, m_records.l2
                               , m_records.s3, m_records.l3);
    m_tetrisWindow.setRecord(m_records.s1, m_records.l1
                             , m_records.s2, m_records.l2
                             , m_records.s3, m_records.l3);
    SaveController::removeGame();
}

void TetrisController::pause()
{
    if (!m_isGameActive) { return; }

    if (m_gameTimer.isActive()) {
        m_soundController.pauseMusic();
        m_gameTimer.stop();
    } else {
        m_soundController.playCurrentMusic();
        m_gameTimer.start(STEP_DELAY);
    }
}

void TetrisController::moveItemleft()
{
    if (!m_isGameActive) { return; }
    m_tetrisModel.moveActiveItemLeft();
}

void TetrisController::moveItemRight()
{
    if (!m_isGameActive) { return; }
    m_tetrisModel.moveActiveItemRight();
}

void TetrisController::rotateItem()
{
    if (!m_isGameActive) { return; }
    m_tetrisModel.rotateActiveItem();
}

void TetrisController::enableAccelerate(bool isAccelerate)
{
    if (!m_isGameActive) { return; }
    int delay = isAccelerate ? STEP_DELAY_MAX : STEP_DELAY;
    m_gameTimer.setInterval(delay);
    this->gameDoStep();
}

void TetrisController::gameDoStep()
{
    if (m_isGameActive && m_tetrisModel.isGameActive() && !m_tetrisWindow.isAnimActive()) {
        m_tetrisWindow.setFocus();
        int speed = STEP_DELAY - (m_tetrisModel.getLevel() - 1) * STEP_DELAY_NEXT_LEVEL;
        m_gameTimer.setInterval(speed);
        m_tetrisModel.doStep();
        redrawGameField();
    } else {
        if (!m_tetrisModel.isGameActive()) {
            this->gameOver();
        }
    }
}

void TetrisController::redrawGameField()
{
    if (m_tetrisWindow.isAnimActive()) { return; }

    m_tetrisWindow.setUpdatesEnabled(false);

    static auto convert = [&](tetrismodel::FCT typeTM) -> TetrisWindow::BlockType {
        switch (typeTM) {
            case tetrismodel::FCT::E : return TetrisWindow::BO;
            case tetrismodel::FCT::I : return TetrisWindow::Bi;
            case tetrismodel::FCT::J : return TetrisWindow::Bj;
            case tetrismodel::FCT::L : return TetrisWindow::Bl;
            case tetrismodel::FCT::O : return TetrisWindow::Bo;
            case tetrismodel::FCT::S : return TetrisWindow::Bs;
            case tetrismodel::FCT::T : return TetrisWindow::Bt;
            case tetrismodel::FCT::Z : return TetrisWindow::Bz;
        }
    };

    QSize fieldSizeBlocks = m_tetrisModel.getSizeBlocks();

    // Перерисовка клеток поля
    for (int i = 0; i < fieldSizeBlocks.height(); ++i) {
        for (int j = 0; j < fieldSizeBlocks.width(); ++j) {      
            tetrismodel::FCT typeTM = m_tetrisModel.getBlockType(QPoint(j,i));
            m_tetrisWindow.addFieldBlock(convert(typeTM), QPoint(j,i));
        }
    }

    // Добавление активного элемента на поле
    TetrisItem activeItem = m_tetrisModel.getActiveItem();

    for (int i = 0; i < activeItem.getSizeBlocks(); ++i) {
        for (int j = 0; j < activeItem.getSizeBlocks(); ++j) {

            int fJ = activeItem.getPosition().x() + j - 1;
            int fI = activeItem.getPosition().y() + i - 1;

            tetrismodel::FCT typeTM = activeItem.getBlockType(QPoint(j,i));
            if (typeTM != tetrismodel::FCT::E) {
                m_tetrisWindow.addFieldBlock(convert(typeTM), QPoint(fJ,fI));
            }
        }
    }

    m_tetrisWindow.setScore(m_tetrisModel.getScore());
    m_tetrisWindow.setLevel(m_tetrisModel.getLevel());

    m_tetrisWindow.setUpdatesEnabled(true);
}

void TetrisController::addRecord(int score, int level)
{
    QVector<int> vs{ score, m_records.s3, m_records.s2, m_records.s1 };
    QVector<int> vl{ level, m_records.l3, m_records.l2, m_records.l1 };
    std::sort(vs.begin(), vs.end());
    std::sort(vl.begin(), vl.end());

    m_records.s3 = vs[1];
    m_records.s2 = vs[2];
    m_records.s1 = vs[3];
    m_records.l3 = vl[1];
    m_records.l2 = vl[2];
    m_records.l1 = vl[3];
}

