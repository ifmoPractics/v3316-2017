#include "pagecontroler.h"

PageControler::PageControler(QObject *parent) : QObject(parent)
{
    gp = new GamePage;
    mp = new MenuPage;
    sp = new ScorePage;

    connect(mp, SIGNAL(resumeGame()), this, SLOT(resumeGame()));
    connect(mp, SIGNAL(newGame()), this, SLOT(newGame()));
    connect(mp, SIGNAL(bestResult()), this, SLOT(showBestResult()));
    connect(sp, SIGNAL(closeScorePage()), this, SLOT(closeScorePage()));
    connect(gp, SIGNAL(closeGamePage()), this, SLOT(closeGamePage()));

}

void PageControler::start(){
    mp->setResumeButton(!saveParam.loadGame().m_gameOver);
    mp->show();
}

void PageControler::newGame(){
    mp->close();
    gp->newGame();
    gp->show();
}

void PageControler::showBestResult(){
    mp->close();
    sp->loadRecords();
    sp->show();
}

void PageControler::closeScorePage(){
    sp->close();
    mp->setResumeButton(!saveParam.loadGame().m_gameOver);
    mp->show();
}

void PageControler::closeGamePage(){
    gp->close();
    mp->setResumeButton(!saveParam.loadGame().m_gameOver);
    mp->show();
}

void PageControler::resumeGame(){
    mp->close();
    gp->resumeGame();
    gp->show();
}




