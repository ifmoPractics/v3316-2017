#include "gamepage.h"

GamePage::GamePage(QWidget *parent) : QMainWindow(parent),
    pict_I(":/images/I.png"),
    pict_J(":/images/J.png"),
    pict_L(":/images/L.png"),
    pict_O(":/images/O.png"),
    pict_S(":/images/S.png"),
    pict_Z(":/images/Z.png"),
    pict_T(":/images/T.png")
{
    this->setFixedSize(510, 350);

    game = new GameField(10, 20, this);
    exit = new QPushButton("Exit");
    label_picture = new QLabel(this);
    //next_figure_pict = new QPixmap(":/images/I.png");
    label_score = new QLabel("Score: 0", this);
    h_layout = new QHBoxLayout;
    v_layout = new QVBoxLayout;
    saveRec = new SaveRecord;
    label_picture->setPixmap(pict_I);

    v_layout->addWidget(label_picture);
    v_layout->addWidget(label_score);
    v_layout->addWidget(exit);

    h_layout->addWidget(game);
    h_layout->addLayout(v_layout);
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(h_layout);
    this->setCentralWidget(centralWidget);

    connect(game, SIGNAL(changedNextFigure(int)),this, SLOT(drawNextFigure(int)));
    connect(game, SIGNAL(changedScore(int)), this, SLOT(writeScore(int)));
    connect(exit, SIGNAL(clicked(bool)), this, SLOT(exitPresed()));
    connect(game, SIGNAL(endGame(int)), this, SLOT(endGamesaveRecord(int)));
    connect(saveRec, SIGNAL(endSaveRecord()), this, SIGNAL(closeGamePage()));

}

void GamePage::keyPressEvent(QKeyEvent *event){
    game->key_event(event);
}

void GamePage::drawNextFigure(int num){
    switch (num) {
    case 0:
        label_picture->setPixmap(pict_I);
        break;
    case 1:
        label_picture->setPixmap(pict_J);
        break;
    case 2:
        label_picture->setPixmap(pict_L);
        break;
    case 3:
        label_picture->setPixmap(pict_O);
        break;
    case 4:
        label_picture->setPixmap(pict_S);
        break;
    case 5:
        label_picture->setPixmap(pict_Z);
        break;
    case 6:
        label_picture->setPixmap(pict_T);
        break;
    }
}

void GamePage::writeScore(int score){
    label_score->setText("Score: " + QString::number(score));
}

void GamePage::newGame(){
    game->initGame();
}

void GamePage::exitPresed(){
    //killTimer(game->getTimerid());
    game->saveGame();
    emit closeGamePage();
}

void GamePage::resumeGame(){
    game->resumeGame();
}

GamePage::~GamePage(){
    delete game;
    delete exit;
    delete label_picture;
    delete label_score;
    delete h_layout;
    delete v_layout;
    delete saveRec;
}

void GamePage::endGamesaveRecord(int score){
    saveRec->setScore(score);
    saveRec->show();

}
