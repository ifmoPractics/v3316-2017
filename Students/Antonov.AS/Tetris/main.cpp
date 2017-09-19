#include "gamepage.h"
#include "pagecontroller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PageController tetris;
    tetris.startTheGame();

    return a.exec();
}

