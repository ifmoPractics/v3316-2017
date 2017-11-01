#include "gamepage.h"
#include "ui_gamepage.h"

GamePage::GamePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GamePage){
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowSystemMenuHint);

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 4; j++){
            m_nextFigureMatrix[i][j] = new QLabel(this);
            m_nextFigureMatrix[i][j]->setPixmap(QPixmap());
            m_nextFigureMatrix[i][j]->setGeometry((j + 13) * m_rectSize, (i + 7.5) * m_rectSize,
                                        m_rectSize, m_rectSize);
        }
    }

    ui->backButton->setEnabled(false);

    connect(ui->gameWidget, SIGNAL(newNextFigure()), this, SLOT(buildNextFigure()));
    connect(ui->gameWidget, SIGNAL(changeLine(int)), this, SLOT(updateLineLabel(int)));
    connect(ui->gameWidget, SIGNAL(changeScore(int)), this, SLOT(updateScoreLabel(int)));
    connect(ui->gameWidget, SIGNAL(endGame()), this, SIGNAL(loseGame()));
    connect(ui->pauseButton, SIGNAL(clicked()), this, SLOT(pauseButtonProcessing()));
    connect(ui->backButton, SIGNAL(clicked()), this, SIGNAL(canceledGame()));
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(saveGame()));
}

void GamePage::buildNextFigure(){
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 4; j++){
            m_nextFigureMatrix[i][j]->setPixmap(QPixmap());
        }
    }
    ui->gameWidget->nextFigure->setCoordinates(Coordinate(1, 1));
    for (int i = 0; i < 4; i++){
        m_nextFigureMatrix[ui->gameWidget->nextFigure->getPoint(i).y][ui->gameWidget->nextFigure->getPoint(i).x]->
                setPixmap(ui->gameWidget->nextFigure->icon());
    }
}

void GamePage::startNewGame(){
    ui->backButton->setEnabled(false);
    ui->gameWidget->startGame();
}

void GamePage::startContinueGame(){
    ui->backButton->setEnabled(true);
    ui->gameWidget->stopGame();
    ui->gameWidget->setParameters(gameSaveController.load());
}

void GamePage::saveGame(){
    gameSaveController.save(ui->gameWidget->getParameters());
}

void GamePage::pauseButtonProcessing(){
    if (!ui->backButton->isEnabled()){
        ui->backButton->setEnabled(true);
        ui->gameWidget->stopGame();
    }
    else{
        ui->backButton->setEnabled(false);
        ui->gameWidget->goGame();
    }
}

void GamePage::updateLineLabel(int line){
    ui->lineLabel->setText("Line: " + QString::number(line));
}

void GamePage::updateScoreLabel(int score){
    ui->scoreLabel->setText("Score: " + QString::number(score));
}

GamePage::~GamePage(){
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 4; j++){
            delete m_nextFigureMatrix[i][j];
        }
    }
    delete ui;
}
