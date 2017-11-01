#ifndef SAVECONTROLLER_H
#define SAVECONTROLLER_H

#include <QObject>
#include <QSettings>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include "figure.h"

struct Record{
    Record(){}
    Record(const Record& other) : place(other.place), name(other.name), score(other.score), line(other.line){}
    Record(int p, QString n, int s, int l) : place(p), name(n), score(s), line(l){}
    Record& operator=(const Record& other);
    int place;
    QString name;
    int score;
    int line;
};

struct SaveParameters{
    SaveParameters(){}
    SaveParameters(const SaveParameters& other);
    SaveParameters(QString m[17][10], int l, int s, QChar t, Coordinate c[4], QChar nextT);
    SaveParameters& operator=(const SaveParameters& other);
    QString matrix[17][10];
    int line;
    int score;
    QChar type;
    QChar nextType;
    Coordinate coordinate[4];
};

class SaveController{
public:
    void save(const SaveParameters& parameters);
    SaveParameters load();

    void saveContinueStatus(bool status);
    bool loadContinueStatus();

    void saveRecord(const Record& record);
    Record getRecord(int n);
    void refreshRecords();
private:
    SaveParameters m_parameters;
};

#endif // SAVECONTROLLER_H
