#include "menupage.h"

MenuPage::MenuPage(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    resume = new QPushButton("Resume", this);
    new_game = new QPushButton("New Game", this);
    best_result = new QPushButton("Best Result", this);
    exit = new QPushButton("Exit", this);
    layout->addWidget(resume);
    layout->addWidget(new_game);
    layout->addWidget(best_result);
    layout->addWidget(exit);
    setLayout(layout);

    connect(resume, SIGNAL(clicked(bool)), this, SIGNAL(resumeGame()));
    connect(new_game, SIGNAL(clicked(bool)), this, SIGNAL(newGame()));
    connect(best_result, SIGNAL(clicked(bool)), this, SIGNAL(bestResult()));
    connect(exit, SIGNAL(clicked(bool)), this, SLOT(close()));
}

void MenuPage::setResumeButton(bool flag){
    resume->setEnabled(flag);
}
