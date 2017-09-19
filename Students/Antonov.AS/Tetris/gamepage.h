#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QWidget>
#include <QPixmap>
#include <QString>

#include "gamecontroller.h"

namespace Ui {
class GamePage;
}

class GamePage : public QWidget{
    Q_OBJECT
public:
    explicit GamePage(QWidget *parent = 0);
    ~GamePage();
signals:
    void loseGame();
    void canceledGame();
public slots:
    void updateLineLabel(int line);
    void updateScoreLabel(int score);

    void startNewGame();
    void startContinueGame();

    void pauseButtonProcessing();
    void saveGame();

    void buildNextFigure();
private:
    Ui::GamePage *ui;
    SaveController gameSaveController;

    QLabel* m_nextFigureMatrix[5][4];

    const int m_rectSize = 16;
};

#endif // GAMEPAGE_H
