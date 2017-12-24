#include "gamefield.h"
#include "gamepage.h"
#include "menupage.h"
#include "scorepage.h"
#include "pagecontroler.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //GameField g(10, 20);
    //g.show();
 //   GamePage gp;
 //   gp.show();
    //MenuPage mp;
    //mp.show();
   // ScorePage sp;
   // sp.loadRecords();
   // sp.show();
    PageControler pg;
    pg.start();
    return a.exec();
}
