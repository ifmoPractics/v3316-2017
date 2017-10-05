#ifndef MENUPAGE_H
#define MENUPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class MenuPage : public QWidget
{
    Q_OBJECT
public:
    explicit MenuPage(QWidget *parent = nullptr);
    void setResumeButton(bool);

signals:
    void resumeGame();
    void newGame();
    void bestResult();

private:
    QVBoxLayout *layout;
    QPushButton *resume;
    QPushButton *new_game;
    QPushButton *best_result;
    QPushButton *exit;
};

#endif // MENUPAGE_H
