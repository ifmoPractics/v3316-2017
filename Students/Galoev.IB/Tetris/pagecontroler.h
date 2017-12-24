#ifndef PAGECONTROLER_H
#define PAGECONTROLER_H

#include <QObject>
#include "gamepage.h"
#include "menupage.h"
#include "scorepage.h"
#include "save.h"


class PageControler : public QObject
{
    Q_OBJECT
public:
    explicit PageControler(QObject *parent = nullptr);
    void start();

private slots:
    void resumeGame();
    void newGame();
    void showBestResult();
    void closeScorePage();
    void closeGamePage();

private:
    GamePage *gp;
    MenuPage *mp;
    ScorePage *sp;
    Save saveParam;
};

#endif // PAGECONTROLER_H
