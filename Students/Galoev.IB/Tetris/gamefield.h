#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QWidget>
#include <vector>
#include <ctime>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include "figures.h"
#include "save.h"

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define BLOCK_SIZE 16
#define INTERVAL 400

class GameField : public QWidget
{
    Q_OBJECT
public:
    explicit GameField(int width, int height, QWidget *parent = nullptr);
    void moveFigureDown();
    void moveFigureLeft();
    void moveFigureRight();
    void rotateFigure();
    void writeFigure();
    void clearFigure();
    bool checkCollisions(Figures& figure);
    void deleteFullLine();
    void initGame();
    void saveGame();
    void resumeGame();
    void key_event(QKeyEvent *);
    int getTimerid () {return timerid;}

protected:
    void paintEvent(QPaintEvent *);

    //void timerEvent(QTimerEvent *);
    //void keyPressEvent(QKeyEvent *event);

signals:
    void changedNextFigure(int);
    void changedScore(int);
    void endGame(int);
private slots:
    void timerend();

private:
    int m_width;
    int m_height;
    int m_speed;
    int m_score;
    bool m_gameOver;
    int m_num_cur;
    int m_num_next;
    std::vector< std::vector<int> > m_field;
    Figures curFigure;
    int timerid;
    Save saveParam;
    QTimer *timer;
};

#endif // GAMEFIELD_H
