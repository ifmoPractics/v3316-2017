#ifndef PAGECONTROLLER_H
#define PAGECONTROLLER_H

#include <QObject>
#include <QApplication>

#include "menupage.h"
#include "gamepage.h"
#include "scorepage.h"

class PageController : public QObject{
    Q_OBJECT
public:
    PageController();
    ~PageController();

    void startTheGame();
private slots:
    void newGameHandler();
    void continueGameHandler();
    void loseGameHandler();
    void canceledGameHandler();
    void bestScoresHandler();
    void closeScorePageHandler();
private:
    MenuPage* menu;
    GamePage* game;
    ScorePage* score;
};

#endif // PAGECONTROLLER_H
