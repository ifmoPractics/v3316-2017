#ifndef SCOREPAGE_H
#define SCOREPAGE_H

#include <QWidget>
#include <QString>
#include "savecontroller.h"

namespace Ui {
class ScorePage;
}

class ScorePage : public QWidget{
    Q_OBJECT
public:
    explicit ScorePage(QWidget *parent = 0);
    ~ScorePage();

    void loadRecords();
signals:
    void closeScorePage();
private slots:
    void refreshRecords();
private:
    Ui::ScorePage *ui;
    SaveController gameSaveController;

    QLabel* m_labels[10];
};

#endif // SCOREPAGE_H
