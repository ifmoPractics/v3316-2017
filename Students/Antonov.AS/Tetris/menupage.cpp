#include "menupage.h"
#include "ui_menupage.h"

MenuPage::MenuPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuPage)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowSystemMenuHint);

    ui->continueGame->setEnabled(gameSaveController.loadContinueStatus());

    connect(ui->newGame, SIGNAL(clicked()), this, SIGNAL(newGame()));
    connect(ui->continueGame, SIGNAL(clicked()), this, SIGNAL(continueGame()));
    connect(ui->bestScores, SIGNAL(clicked()), this, SIGNAL(bestScores()));
    connect(ui->exit, SIGNAL(clicked()), this, SLOT(exitGame()));
}

void MenuPage::showWithoutContinue(){
    ui->continueGame->setEnabled(false);
    this->show();
}

void MenuPage::showWithContinue(){
    ui->continueGame->setEnabled(true);
    this->show();
}

void MenuPage::exitGame(){
   gameSaveController.saveContinueStatus(ui->continueGame->isEnabled());
   this->close();
}

MenuPage::~MenuPage(){
    delete ui;
}
