#ifndef SAVERECORDDIALOG_H
#define SAVERECORDDIALOG_H

#include <QDialog>
#include "savecontroller.h"

namespace Ui {
class SaveRecordDialog;
}

class SaveRecordDialog : public QDialog{
    Q_OBJECT
public:
    explicit SaveRecordDialog(QWidget *parent = 0);
    ~SaveRecordDialog();

    void setValues(int score, int line);
private slots:
    void saveRecord();
private:
    Ui::SaveRecordDialog *ui;
    SaveController gameSaveController;
    int records[10];
};

#endif // SAVERECORDDIALOG_H
