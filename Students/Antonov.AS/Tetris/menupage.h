#ifndef MENUPAGE_H
#define MENUPAGE_H

#include <QWidget>

#include "savecontroller.h"

namespace Ui {
class MenuPage;
}

class MenuPage : public QWidget{
    Q_OBJECT
public:
    explicit MenuPage(QWidget *parent = 0);
    ~MenuPage();
signals:
    void newGame();
    void continueGame();
    void bestScores();
public slots:
    void showWithoutContinue();
    void showWithContinue();
    void exitGame();
private:
    Ui::MenuPage *ui;
    SaveController gameSaveController;
};

#endif // MENUPAGE_H
