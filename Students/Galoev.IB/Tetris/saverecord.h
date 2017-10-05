#ifndef SAVERECORD_H
#define SAVERECORD_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include "save.h"

class SaveRecord : public QWidget
{
    Q_OBJECT
public:
    explicit SaveRecord(QWidget *parent = nullptr);
    ~SaveRecord();
    void setScore(int score);
private slots:
    void okClicked();
signals:
    void endSaveRecord();

private:
    QLabel *lbl;
    QLineEdit *line;
    QPushButton *ok;
    Save saveParam;
    int m_score;
};

#endif // SAVERECORD_H
