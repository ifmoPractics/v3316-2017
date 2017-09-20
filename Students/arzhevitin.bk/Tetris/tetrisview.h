/* Файл реализации Представления
 * Вывод игрового поля и основного модуля игры
**/

#pragma once

#include "tetriscontroller.h"
#include "tetrismodel.h"


#include <QtWidgets>
#include <QKeyEvent>

const QSize MAX_GAME_FIELD_SIZE(300,750); //1:2.5

//------------------------------------------------------
class TetrisView : public QWidget
{
    Q_OBJECT

public:
    explicit TetrisView(QWidget *parent = 0);
    ~TetrisView();

    int getScore();

signals:
    void gameOver();

public slots:
    void pauseGame();
    void exitGame();

protected:
    void paintEvent(QPaintEvent* ) override;
    void keyPressEvent(QKeyEvent* pe) override;
    void keyReleaseEvent(QKeyEvent* pe) override;

private:
    void    loadPictures();
    QPixmap getPixmap(tetrismodel::FCT type);

private:
    TetrisModel         m_tetrisModel;
    TetrisController*   m_tetrisController;

    QWidget* m_gameField;
    QLCDNumber* m_scoreLcd;
    QLCDNumber* m_levelLcd;

    QPixmap img_i, img_j,
            img_l, img_o,
            img_s, img_t,
            img_z, img_e;
    int m_boxSize;

    QVector<QVector<QLabel*> > m_imgField; // массив картинок
};
