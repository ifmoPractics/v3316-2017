#ifndef CREATENEWSTATIONDIALOG_H
#define CREATENEWSTATIONDIALOG_H

#include <QDialog>

namespace Ui {
class CreateNewStationDialog;
}

class CreateNewStationDialog : public QDialog{
    Q_OBJECT

public:
    explicit CreateNewStationDialog(QWidget *parent = 0);
    ~CreateNewStationDialog();

signals:
    void stationInitialized(bool, QString, int);

private slots:
    void dataChecking();
    void closeDialog();

private:
    Ui::CreateNewStationDialog *ui;
};

#endif // CREATENEWSTATIONDIALOG_H
