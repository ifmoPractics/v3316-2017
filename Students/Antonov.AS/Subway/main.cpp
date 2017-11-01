#include "subwaymap.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    SubwayMap w;
    w.show();

    return a.exec();
}
