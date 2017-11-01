#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QFrame>
#include <QTimer>
#include <QPixmap>
#include <QKeyEvent>
#include <QTime>
#include <QCoreApplication>

#include "figure.h"
#include "savecontroller.h"
#include "saverecorddialog.h"

class GameController : public QFrame{
    Q_OBJECT
public:
    explicit GameController(QWidget *parent = nullptr);
    ~GameController();

    void startGame();

    void initilizeGame();
    SaveParameters getParameters() const;
    void setParameters(const SaveParameters& parameters);

    void buildingFigure();
    void rebuildingFigure();

    void getRandomFigure();
    void turnFigure();

    bool isCollision(const Direct& direct) const;
    void deleteLines();
    bool lose() const;

    void delay(int millisecondsToWait);

    void createNextFigure();
    Figure* nextFigure;
signals:
    void changeLine(int line);
    void changeScore(int score);
    void changeBestScore();
    void endGame();
    void newNextFigure();
public slots:
    void moveFigure();
    void moveFigure(const Direct& direct);
    void stopGame();
    void goGame();
private:
    const int height = 17;
    const int width = 10;
    const int m_rectSize = 16;

    void keyPressEvent(QKeyEvent* event);

    QLabel* m_matrix[17][10];
    Figure* m_currentFigure;
    QTimer* m_timer;
    SaveRecordDialog* m_saveRecordDialog;
    int m_turn;
    int m_score;
    int m_line;
};

#endif // GAMECONTROLLER_H
