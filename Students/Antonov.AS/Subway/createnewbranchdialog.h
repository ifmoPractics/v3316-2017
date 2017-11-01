#ifndef CREATENEWBRANCHDIALOG_H
#define CREATENEWBRANCHDIALOG_H

#include <QDialog>

namespace Ui {
class CreateNewBranchDialog;
}

class CreateNewBranchDialog : public QDialog{
    Q_OBJECT

public:
    explicit CreateNewBranchDialog(QWidget *parent = 0);
    ~CreateNewBranchDialog();

signals:
    void branchInitialized(QString, QString, QColor);
private slots:
    void dataChecking();
    void closeDialog();
private:
    Ui::CreateNewBranchDialog *ui;
};

#endif // CREATENEWBRANCHDIALOG_H
