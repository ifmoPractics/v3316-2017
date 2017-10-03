#include <QApplication>
#include "tetriscontroller.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TetrisController game;
    game.startGameTetris();

    return a.exec();
}
