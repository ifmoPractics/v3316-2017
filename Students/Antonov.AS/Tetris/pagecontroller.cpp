#include "pagecontroller.h"

PageController::PageController(){
    QFile file(":/style.qss");
    if(file.open(QFile::ReadOnly)) {
       QString StyleSheet = QLatin1String(file.readAll());
       qApp->setStyleSheet(StyleSheet);
    }

    menu = new MenuPage();
    game = new GamePage();
    score = new ScorePage();

    connect(menu, SIGNAL(newGame()), this, SLOT(newGameHandler()));
    connect(menu, SIGNAL(continueGame()), this, SLOT(continueGameHandler()));
    connect(menu, SIGNAL(bestScores()), this, SLOT(bestScoresHandler()));

    connect(game, SIGNAL(loseGame()), this, SLOT(loseGameHandler()));
    connect(game, SIGNAL(canceledGame()), this, SLOT(canceledGameHandler()));

    connect(score, SIGNAL(closeScorePage()), this, SLOT(closeScorePageHandler()));
}

void PageController::startTheGame(){
    menu->show();
}

void PageController::loseGameHandler(){
    game->close();
    menu->showWithoutContinue();
}

void PageController::canceledGameHandler(){
    game->close();
    menu->showWithContinue();
}

void PageController::newGameHandler(){
    menu->close();
    game->startNewGame();
    game->show();
}

void PageController::continueGameHandler(){
    menu->close();
    game->startContinueGame();
    game->show();
}

void PageController::bestScoresHandler(){
    menu->close();
    score->loadRecords();
    score->show();
}

void PageController::closeScorePageHandler(){
    score->close();
    menu->show();
}

PageController::~PageController(){
    delete menu;
    delete game;
    delete score;
}
