#ifndef MAKERINGORLINEDIALOG_H
#define MAKERINGORLINEDIALOG_H

#include <QDialog>

namespace Ui {
class MakeRingOrLineDialog;
}

class MakeRingOrLineDialog : public QDialog{
    Q_OBJECT

public:
    explicit MakeRingOrLineDialog(QWidget *parent = 0);
    ~MakeRingOrLineDialog();

signals:
    void makeRingDone(int);

public slots:
    void setStations(const QString& station1, const QString& station2);

private slots:
    void dataChecking();
    void closeDialog();

private:
    Ui::MakeRingOrLineDialog *ui;
};

#endif // MAKERINGORLINEDIALOG_H
