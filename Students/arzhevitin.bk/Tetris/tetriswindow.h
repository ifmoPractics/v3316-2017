#ifndef TETRISWINDOW_H
#define TETRISWINDOW_H

#include <QWidget>
#include <QLCDNumber>
#include <QPushButton>
#include <QPoint>
#include <QMap>
#include <QLabel>
#include <QWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QVector>

class TetrisWindow : public QWidget
{
    Q_OBJECT

public:
    TetrisWindow(QWidget *parent = nullptr);
    ~TetrisWindow();

    enum BlockType {
        Bi, Bj, Bl, Bo, Bs, Bt, Bz,
        BO/* Block Opasity*/, BT /* Block Title*/
    };

public:
    void addFieldBlock(BlockType, QPoint);
    void setScore(int );
    void setLevel(int );
    void setRecord(int s1, int l1, int s2, int l2, int s3, int l3);
    void showRecords();
    void showGameover();
    void showPageChange();
    void showTitle();
    void showEnd();
    bool isAnimActive();

signals:
    void on_switchOn();
    void on_pushBtnNewgame();
    void on_pushBtnContinue();
    void on_pushBtnRecords();
    void on_pushBtnExit();
    void on_moveLeft();
    void on_moveRight();
    void on_rotate();
    void on_accelerate(bool);
    void on_keyPause();

protected:
    void mousePressEvent(QMouseEvent* ) override;
    void mouseMoveEvent(QMouseEvent* ) override;
    void keyPressEvent(QKeyEvent *) override;
    void keyReleaseEvent(QKeyEvent *) override;

private slots:
    void pushBtnNewgame();
    void pushBtnContinue();
    void pushBtnRecords();
    void pushBtnExit();
    void animPageChange();
    void animSwichOn();
    void animSwichOff();
    void animRecords();
    void animGameover();

private:
    void initField();

private:
    QPoint m_ptPosition;
    QPushButton *m_ptPushBtnNewgame;
    QPushButton *m_ptPushBtnContinue;
    QPushButton *m_ptPushBtnRecords;
    QPushButton *m_ptPushBtnExit;
    QLCDNumber *m_lcdNumScore;
    QLCDNumber *m_lcdNumLevel;
    QWidget *m_gameField;
    const QSize m_fieldSize = {10, 20};

    QMap<BlockType, QPixmap> m_BlockImg;
    //QPixmap m_BlockImg[9];
    QVector<QVector<QLabel*> > m_gameFieldBlocks;

    bool m_isAnimActive;
    bool m_isAnimPageChange = false, m_isAnimSwichOn = false,
         m_isAnimSwichOff = false, m_isAnimeGameover = false,
         m_isAnimRecords = false;

    QTimer *m_timerAnimPageChange;
    QTimer *m_timerAnimSwichOn;
    QTimer *m_timerAnimSwichOff;
    QTimer *m_timerAnimGameover;
    QTimer *m_timerAnimRecords;

    struct Records { int s1 = 0; int s2 = 0; int s3 = 0;
                     int l1 = 0; int l2 = 0; int l3 = 0;
                   } m_records;
};

#endif // TETRISWINDOW_H
