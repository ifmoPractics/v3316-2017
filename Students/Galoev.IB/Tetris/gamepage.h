#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QMainWindow>
#include "gamefield.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include "saverecord.h"

class GamePage : public QMainWindow
{
    Q_OBJECT
public:
    explicit GamePage(QWidget *parent = nullptr);
    ~GamePage();
    void newGame();
    void resumeGame();

protected:
    void keyPressEvent(QKeyEvent *event);

signals:
    void closeGamePage();

private slots:
    void drawNextFigure(int);
    void writeScore(int);
    void exitPresed();
    void endGamesaveRecord(int n);

private:
    GameField *game;
    QPushButton *exit;
    QLabel* label_picture;
    QLabel* label_score;
    QHBoxLayout* h_layout;
    QVBoxLayout* v_layout;
    const QPixmap pict_I;
    const QPixmap pict_J;
    const QPixmap pict_L;
    const QPixmap pict_O;
    const QPixmap pict_S;
    const QPixmap pict_Z;
    const QPixmap pict_T;
    SaveRecord *saveRec;
};

#endif // GAMEPAGE_H
