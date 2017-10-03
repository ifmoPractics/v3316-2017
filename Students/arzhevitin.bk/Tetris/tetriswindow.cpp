#include "tetriswindow.h"

#include <algorithm>
#include <random>
#include <QFile>

TetrisWindow::TetrisWindow(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::Window)
{
    QFile file;
    file.setFileName(":/style.css");
    file.open(QIODevice::ReadOnly);
    setStyleSheet(file.readAll());
    file.close();

    QPixmap pix(":/img/back.png");
    QLabel *background = new QLabel(this);
    background->setPixmap(pix);
    setAttribute(Qt::WA_TranslucentBackground);
    resize(pix.size());

    setFocus();

    m_BlockImg.insert(Bi, QPixmap(":/img/block_i.png"));
    m_BlockImg.insert(Bj, QPixmap(":/img/block_j.png"));
    m_BlockImg.insert(Bl, QPixmap(":/img/block_l.png"));
    m_BlockImg.insert(Bo, QPixmap(":/img/block_o.png"));
    m_BlockImg.insert(Bs, QPixmap(":/img/block_s.png"));
    m_BlockImg.insert(Bt, QPixmap(":/img/block_t.png"));
    m_BlockImg.insert(Bz, QPixmap(":/img/block_z.png"));
    m_BlockImg.insert(BO, QPixmap(":/img/block_back_field.png"));
    m_BlockImg.insert(BT, QPixmap(":/img/block_back_title.png"));


    m_lcdNumScore = new QLCDNumber(this);
    m_lcdNumScore->setGeometry(429, 97, 114, 41);
    m_lcdNumScore->setSegmentStyle(QLCDNumber::Flat);
    m_lcdNumLevel = new QLCDNumber(this);
    m_lcdNumLevel->setGeometry(429, 191, 114, 41);
    m_lcdNumLevel->setSegmentStyle(QLCDNumber::Flat);

    m_gameField = new QWidget(this);
    m_gameField->setGeometry(136, 80, 228, 452);
    m_gameField->setObjectName("field");
    initField();

    QLabel *frameGameField = new QLabel(this);
    frameGameField->setPixmap(QPixmap(":/img/up_field_frame.png"));
    frameGameField->setGeometry(109, 56, 280, 503);

    QLabel *frameScore = new QLabel(this);
    frameScore->setPixmap(QPixmap(":/img/up_score_frame.png"));
    frameScore->setGeometry(423, 91, 125, 52);
    QLabel *frameLevel = new QLabel(this);
    frameLevel->setPixmap(QPixmap(":/img/up_level_frame.png"));
    frameLevel->setGeometry(422, 184, 125, 52);

    m_ptPushBtnNewgame = new QPushButton(this);
    m_ptPushBtnNewgame->setGeometry(421, 296, 50, 50);
    m_ptPushBtnContinue = new QPushButton(this);
    m_ptPushBtnContinue->setGeometry(421, 354, 50, 50);
    m_ptPushBtnRecords = new QPushButton(this);
    m_ptPushBtnRecords->setGeometry(421, 411, 50, 50);
    m_ptPushBtnExit = new QPushButton(this);
    m_ptPushBtnExit->setGeometry(421, 468, 50, 50);
    connect(m_ptPushBtnNewgame, SIGNAL(released()), SLOT(pushBtnNewgame()));
    connect(m_ptPushBtnContinue, SIGNAL(released()), SLOT(pushBtnContinue()));
    connect(m_ptPushBtnRecords, SIGNAL(released()), SLOT(pushBtnRecords()));
    connect(m_ptPushBtnExit, SIGNAL(released()), SLOT(pushBtnExit()));

    m_timerAnimPageChange = new QTimer(this);
    m_timerAnimSwichOn = new QTimer(this);
    m_timerAnimSwichOff = new QTimer(this);
    m_timerAnimGameover = new QTimer(this);
    m_timerAnimRecords = new QTimer(this);
    connect(m_timerAnimPageChange, SIGNAL(timeout()), SLOT(animPageChange()));
    connect(m_timerAnimSwichOn, SIGNAL(timeout()), SLOT(animSwichOn()));
    connect(m_timerAnimSwichOff, SIGNAL(timeout()), SLOT(animSwichOff()));
    connect(m_timerAnimGameover, SIGNAL(timeout()), SLOT(animGameover()));
    connect(m_timerAnimRecords, SIGNAL(timeout()), SLOT(animRecords()));

    showTitle();

}

TetrisWindow::~TetrisWindow()
{

}

void TetrisWindow::addFieldBlock(TetrisWindow::BlockType t, QPoint p)
{
    m_gameFieldBlocks[p.y()][p.x()]->setPixmap(m_BlockImg[t]);
}

void TetrisWindow::setScore(int v)
{
    m_lcdNumScore->display(v);
    repaint();
}

void TetrisWindow::setLevel(int v)
{
    m_lcdNumLevel->display(v);
}

void TetrisWindow::setRecord(int s1, int l1, int s2, int l2, int s3, int l3)
{
    m_records.s1 = s1;
    m_records.l1 = l1;
    m_records.s2 = s2;
    m_records.l2 = l2;
    m_records.s3 = s3;
    m_records.l3 = l3;
}

void TetrisWindow::showRecords()
{
    if (!(m_isAnimPageChange || m_isAnimSwichOn || m_isAnimSwichOff ||
        m_isAnimeGameover)) {
        m_isAnimRecords = true;
    }
    m_timerAnimRecords->start(400);
}

void TetrisWindow::showGameover()
{
    if (!(m_isAnimPageChange || m_isAnimSwichOn || m_isAnimSwichOff ||
         m_isAnimRecords)) {
        m_isAnimeGameover = true;
    }
    m_timerAnimGameover->start(10);
}

void TetrisWindow::showPageChange()
{
    if (!(m_isAnimSwichOn || m_isAnimSwichOff ||
        m_isAnimeGameover || m_isAnimRecords)) {
        m_isAnimPageChange = true;
    }
    m_timerAnimPageChange->start(15);
}

void TetrisWindow::showTitle()
{
    if (!(m_isAnimPageChange || m_isAnimSwichOff ||
        m_isAnimeGameover || m_isAnimRecords)) {
        m_isAnimSwichOn = true;
    }

    emit on_switchOn();

    m_timerAnimSwichOn->start(5);
}

void TetrisWindow::showEnd()
{
    if (!(m_isAnimPageChange || m_isAnimSwichOn ||
        m_isAnimeGameover || m_isAnimRecords)) {
         m_isAnimSwichOff = true;
    }

    m_timerAnimSwichOff->start(10);
}

bool TetrisWindow::isAnimActive()
{
    return m_isAnimActive;
}

void TetrisWindow::mousePressEvent(QMouseEvent *pe)
{
    m_ptPosition = pe->pos();
}

void TetrisWindow::mouseMoveEvent(QMouseEvent *pe)
{
    move(pe->globalPos() - m_ptPosition);
}

void TetrisWindow::keyPressEvent(QKeyEvent *pe)
{
    switch(pe->key()) {
    case Qt::Key_Up :
    case Qt::Key_W : {
        emit on_rotate();
        break;
    }
    case Qt::Key_Down :
    case Qt::Key_S : {
        emit on_accelerate(true);
        break;
    }
    case Qt::Key_Left :
    case Qt::Key_A : {
        emit on_moveLeft();
        break;
    }
    case Qt::Key_Right :
    case Qt::Key_D : {
        emit on_moveRight();
        break;
    }
    case Qt::Key_Space :
    case Qt::Key_P : {
        emit on_keyPause();
    }
    default:
        QWidget::keyPressEvent(pe);
    }
}

void TetrisWindow::keyReleaseEvent(QKeyEvent *pe)
{
    switch(pe->key()){
    case Qt::Key_Down :
    case Qt::Key_S : {
        emit on_accelerate(false);
        break;
    }
    default:
        QWidget::keyPressEvent(pe);
    }
}

void TetrisWindow::pushBtnNewgame()
{
    if (m_isAnimActive) { return; }
    emit on_pushBtnNewgame();
    showPageChange();
}

void TetrisWindow::pushBtnContinue()
{
    if (m_isAnimActive) { return; }
    emit on_pushBtnContinue();
    showPageChange();
}

void TetrisWindow::pushBtnRecords()
{
    if (m_isAnimActive) { return; }
    emit on_pushBtnRecords();
    showPageChange();
    showRecords();
}

void TetrisWindow::pushBtnExit()
{
    if (m_isAnimActive) { return; }
    emit on_pushBtnExit();
    showEnd();
}

void TetrisWindow::animPageChange()
{
    if (m_isAnimSwichOn || m_isAnimSwichOff ||
        m_isAnimeGameover || m_isAnimRecords ) {
        return;
    }

    static int r;
    static bool isFirst;
    if (!m_isAnimActive) {
        r = 1;
        isFirst = true;
        m_isAnimActive = true;
    }

    for (float i(0); i < (float)m_fieldSize.height(); i+= 0.05) {
        float k = r*r - pow((i - 10),2);
        if (k < 0) { continue; }
        int j = floorf(sqrt(k));
        if (j >= m_fieldSize.width()) { j = m_fieldSize.width()-1; }
        m_gameFieldBlocks[i][j]->setPixmap(m_BlockImg[ (isFirst)? Bz : BO ]);
    }
    ++r;

    if (r >= m_fieldSize.height() && !isFirst) {
        m_timerAnimPageChange->stop();
        m_isAnimActive = false;
        m_isAnimPageChange = false;
        setScore(0);
        setLevel(0);
    }
    if (r >= m_fieldSize.height()) {
        isFirst = false;
        r = 1;
    }
}

void TetrisWindow::animSwichOn()
{
    if (m_isAnimPageChange || m_isAnimSwichOff ||
        m_isAnimeGameover || m_isAnimRecords ) {
        return;
    }

    static int animI, animJ;
    static QVector<QPoint> pointsOfLetter = {
        {2,1}, {2,2}, {2,3}, {2,5}, {2,6}, {2,7},
        {3,2}, {3,5},
        {4,2}, {4,5}, {4,6}, {4,7},
        {5,2}, {5,5},
        {6,2}, {6,5}, {6,6}, {6,7},
        {8,1}, {8,2}, {8,3}, {8,5}, {8,6}, {8,7},
        {9,2}, {9,5}, {9,7},
        {10,2}, {10,5}, {10,6},
        {11,2}, {11,5}, {11,7},
        {12,2}, {12,5}, {12,7},
        {14,1}, {14,2}, {14,3}, {14,5}, {14,6}, {14,7},
        {15,2}, {15,5},
        {16,2}, {16,5}, {16,6}, {16,7},
        {17,2}, {17,7},
        {18,1}, {18,2}, {18,3}, {18,5}, {18,6}, {18,7},
    };

    if (!m_isAnimActive) {
        animI = 0;
        animJ = 0;
        m_isAnimActive = true;
    }

    m_gameFieldBlocks[animI][animJ]->setPixmap(m_BlockImg[BT]);

    foreach (QPoint p, pointsOfLetter) {
        m_gameFieldBlocks[p.x()][p.y()]->setPixmap(m_BlockImg[Bo]);
    }

    if (++animJ >= m_fieldSize.width()) {
        if (++animI >= m_fieldSize.height()){
            m_timerAnimSwichOn->stop();
            m_isAnimActive = false;
            m_isAnimSwichOn = false;
        }
        animJ = 0;
    }
}

void TetrisWindow::animSwichOff()
{
    if (m_isAnimPageChange || m_isAnimSwichOn ||
        m_isAnimeGameover || m_isAnimRecords ) {
        return;
    }

    static int animI, animJ;
    static QVector<QPoint> pointsOfLetter = {
        {2,1}, {2,2}, {2,3}, {2,5}, {2,6}, {2,7},
        {3,2}, {3,5},
        {4,2}, {4,5}, {4,6}, {4,7},
        {5,2}, {5,5},
        {6,2}, {6,5}, {6,6}, {6,7},
        {8,1}, {8,2}, {8,3}, {8,5}, {8,6}, {8,7},
        {9,2}, {9,5}, {9,7},
        {10,2}, {10,5}, {10,6},
        {11,2}, {11,5}, {11,7},
        {12,2}, {12,5}, {12,7},
        {14,1}, {14,2}, {14,3}, {14,5}, {14,6}, {14,7},
        {15,2}, {15,5},
        {16,2}, {16,5}, {16,6}, {16,7},
        {17,2}, {17,7},
        {18,1}, {18,2}, {18,3}, {18,5}, {18,6}, {18,7},
    };

    if (!m_isAnimActive) {
        animI = 0;
        animJ = 0;
        m_isAnimActive = true;

        for(int i = 0; i < m_fieldSize.height(); ++i) {
            for (int j = 0; j < m_fieldSize.width(); ++j){
                m_gameFieldBlocks[i][j]->setPixmap(m_BlockImg[BT]);
            }
        }
    }

    m_gameFieldBlocks[animI][animJ]->setPixmap(m_BlockImg[BO]);

    foreach (QPoint p, pointsOfLetter) {
        m_gameFieldBlocks[p.x()][p.y()]->setPixmap(m_BlockImg[Bo]);
    }

    if (++animJ >= m_fieldSize.width()) {
        if (++animI >= m_fieldSize.height()){
            m_timerAnimSwichOn->stop();
            m_isAnimActive = false;
            m_isAnimSwichOff = false;
            close();
        }
        animJ = 0;
    }
}

void TetrisWindow::animRecords()
{
    if (m_isAnimPageChange || m_isAnimSwichOn || m_isAnimSwichOff ||
        m_isAnimeGameover  ) {
        return;
    }

    static int state, animJ, update;
    static QVector<QVector<BlockType>> tmpR1 = {
        { BO, BO, Bo, BO },
        { BO, Bo, Bo, BO },
        { BO, BO, Bo, BO },
        { BO, BO, Bo, BO },
        { Bo, Bo, Bo, Bo },
    };
    static QVector<QVector<BlockType>> tmpR2 = {
        { Bi, Bi, Bi, Bi },
        { Bi, BO, BO, Bi },
        { BO, BO, Bi, BO },
        { BO, Bi, BO, BO },
        { Bi, Bi, Bi, Bi },
    };
    static QVector<QVector<BlockType>> tmpR3 = {
        { Bl, Bl, Bl, Bl },
        { Bl, BO, BO, Bl },
        { BO, BO, Bl, BO },
        { BO, BO, BO, Bl },
        { Bl, Bl, Bl, Bl },
    };
    static QVector<QVector<BlockType>> tmpA1 = {
        { BO, Bo, BO },
        { BO, BO, Bo },
        { BO, Bo, BO },
        { BO, BO, BO },
        { BO, Bo, BO },
        { BO, BO, Bo },
        { BO, Bo, BO },
    };
    static QVector<QVector<BlockType>> tmpA2 = {
        { BO, Bi, BO },
        { BO, BO, Bi },
        { BO, Bi, BO },
        { BO, BO, BO },
        { BO, Bi, BO },
        { BO, BO, Bi },
        { BO, Bi, BO },
    };
    static QVector<QVector<BlockType>> tmpA3 = {
        { BO, Bl, BO },
        { BO, BO, Bl },
        { BO, Bl, BO },
        { BO, BO, BO },
        { BO, Bl, BO },
        { BO, BO, Bl },
        { BO, Bl, BO },
    };

    auto fooSetBlocksR = [&](const QVector<QVector<BlockType>>& tmpR) {
        for (int i(0); i < tmpR.size(); i++) {
            for (int j(0); j < tmpR[0].size(); j++) {
                m_gameFieldBlocks[i+10][j+3]->setPixmap(m_BlockImg[tmpR[i][j]]);
            }
        }
    };

    auto fooSetBlocksA = [&](const QVector<QVector<BlockType>>& tmpA) {
        for (int i(0); i < tmpA.size(); i++) {
            for (int j(0); j < tmpA[0].size(); j++) {
                if (j+animJ >= m_gameFieldBlocks[i].size()) { continue; }
                m_gameFieldBlocks[i][j+animJ]->setPixmap(m_BlockImg[tmpA[i][j]]);
            }
        }
    };

    if (!m_isAnimActive) {
        state = 1;
        animJ = 0;
        update = 1;
        m_isAnimActive = true;
    }

    switch (state) {
    case 1:
        fooSetBlocksR(tmpR1);
        fooSetBlocksA(tmpA1);
        if (update) {
            setScore(m_records.s1);
            setLevel(m_records.l1);
            update = 0;
        }
        break;
    case 2:
        fooSetBlocksR(tmpR2);
        fooSetBlocksA(tmpA2);
        if (update) {
            setScore(m_records.s2);
            setLevel(m_records.l2);
            update = 0;
        }
        break;
    case 3:
        fooSetBlocksR(tmpR3);
        fooSetBlocksA(tmpA3);
        if (update) {
            setScore(m_records.s3);
            setLevel(m_records.l3);
            update = 0;
        }
        break;
    }

    if (++animJ >= m_fieldSize.width()) {
        animJ = 0;
        update = 1;
        if (++state > 3) {
            m_timerAnimRecords->stop();
            m_isAnimActive = false;
            m_isAnimRecords = false;
            showPageChange();
            showTitle();
        }
    }
}

void TetrisWindow::animGameover()
{
    if (m_isAnimPageChange || m_isAnimSwichOn || m_isAnimSwichOff ||
         m_isAnimRecords ) {
        return;
    }

    static QVector<QVector<BlockType>> tmpH1 = {
        { BO, BO, Bs, Bs, BO, BO, Bs, Bs, BO, BO },
        { BO, Bs, Bs, Bs, Bs, Bs, Bs, Bs, Bs, BO },
        { BO, Bs, Bs, Bs, Bs, Bs, Bs, Bs, Bs, BO },
        { BO, BO, Bs, Bs, Bs, Bs, Bs, Bs, BO, BO },
        { BO, BO, BO, Bs, Bs, Bs, Bs, BO, BO, BO },
        { BO, BO, BO, BO, Bs, Bs, BO, BO, BO, BO },
    };
    static QVector<QVector<BlockType>> tmpH2 = {
        { BO, Bs, Bs, BO, BO, BO, BO, Bs, Bs, BO },
        { Bs, Bs, Bs, Bs, Bs, BO, Bs, Bs, Bs, Bs },
        { Bs, Bs, Bs, Bs, BO, Bs, Bs, Bs, Bs, Bs },
        { BO, Bs, Bs, Bs, Bs, BO, Bs, Bs, Bs, BO },
        { BO, BO, Bs, Bs, BO, Bs, Bs, Bs, BO, BO },
        { BO, BO, BO, Bs, Bs, BO, Bs, BO, BO, BO },
    };

    static int state, animN, animI, animJ;

    auto fooSetBlocks = [&](const QVector<QVector<BlockType>>& tmp) {
        for (int i(0); i < tmp.size(); i++) {
            for (int j(0); j < tmp[0].size(); j++) {
                m_gameFieldBlocks[i+5][j]->setPixmap(m_BlockImg[tmp[i][j]]);
            }
        }
    };

    if (!m_isAnimActive) {
        animI = 0;
        animJ = 0;
        state = 1;
        animN = 0;
        m_isAnimActive = true;
    }

    switch (state) {
    case 1:
        m_gameFieldBlocks[animI][animJ]->setPixmap(m_BlockImg[BO]);
        break;
    case 2:
        fooSetBlocks(tmpH1);
        state = (animN++/15%2)+2; //каждые 10 кадров, переход к state 3
        break;
    case 3:
        fooSetBlocks(tmpH2);
        state = (animN++/15%2)+2; //каждые 10 кадров, переход к state 2
        break;
    }

    if (++animJ >= m_fieldSize.width()) {
        animJ = 0;
        if (++animI >= m_fieldSize.height()){
            state = 2;
            if (animN >= 200) {
                m_timerAnimGameover->stop();
                m_isAnimActive = false;
                m_isAnimeGameover = false;
                showPageChange();
                showTitle();
            }
        }
    }
}

void TetrisWindow::initField()
{
    for (int i(0); i < m_fieldSize.height(); ++i){
        QVector<QLabel*> tmp;
        for (int j(0); j < m_fieldSize.width(); ++j){   
            tmp.push_back(new QLabel(m_gameField));
            tmp[j]->setPixmap(m_BlockImg[BO]);
            tmp[j]->setGeometry((20+2)*j+4, (19+3)*i+8, 20, 19);
        }
        m_gameFieldBlocks.push_back(tmp);
    }
}
