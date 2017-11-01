#ifndef CREATEJUNCTIONDIALOG_H
#define CREATEJUNCTIONDIALOG_H

#include <QDialog>

namespace Ui {
class CreateJunctionDialog;
}

class CreateJunctionDialog : public QDialog{
    Q_OBJECT

public:
    explicit CreateJunctionDialog(QWidget *parent = 0);
    void setNewBranch(const QString& branchName);
    void setNewStation(int branchNumber, bool isNextStation, const QString& stationName);

    ~CreateJunctionDialog();
signals:
    void junctionInitialized(QList<QPair<int,int> >, QList<int>);

private slots:
    void dataChecking();
    void closeDialog();

    void checkingNumberOfStation(int number);

    void boxChecking1(int currentIndex);
    void boxChecking2(int currentIndex);
    void boxChecking3(int currentIndex);

    void stationChecking1(int);
    void stationChecking2(int);
    void stationChecking3(int);

private:
    Ui::CreateJunctionDialog *ui;
    QList<QStringList> m_stantionsName;
    QList<QPair<int,int> > m_usedStations;
};

#endif // CREATEJUNCTIONDIALOG_H
