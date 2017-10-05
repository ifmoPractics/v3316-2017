#ifndef SCOREPAGE_H
#define SCOREPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "save.h"

class ScorePage : public QWidget
{
    Q_OBJECT
public:
    explicit ScorePage(QWidget *parent = nullptr);
    void loadRecords();

signals:
    void closeScorePage();

private:
    QVBoxLayout* layout;
    QPushButton* button_ok;
    QLabel* m_labels[5];
    Save saveParam;
};

#endif // SCOREPAGE_H
