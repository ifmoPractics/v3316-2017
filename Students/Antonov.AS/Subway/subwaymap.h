#ifndef SUBWAYMAP_H
#define SUBWAYMAP_H

#include <QWidget>
#include <QGraphicsScene>
#include <QList>
#include <QFile>
#include <QApplication>
#include <QObject>
#include <vector>

#include "station.h"
#include "junction.h"
#include "makeringorlinedialog.h"
#include "createnewbranchdialog.h"
#include "createnewstationdialog.h"
#include "createjunctiondialog.h"

namespace Ui {
class SubwayMap;
}

class SubwayMap : public QWidget{
    Q_OBJECT

public:
    explicit SubwayMap(QWidget *parent = 0);
    ~SubwayMap();

private slots:
    void createStation(const QString& branchName, const QString& firstStationName, const QColor& color);
    void addStation(bool isNextStation, const QString& stationName, int lengthOfDistance);
    void swapPanel(int index);
    void makeRing(int lengthOfDistance);
    void checkBranchForEnabledMakeRingButton();

    void showMakeRingDialog();

    void createJunction(const QList<QPair<int,int>>& indexesOfStations, const QList<int>& junctionLengths);

    void setGraphValue(int firstStation, int secondStation, int lengthOfDistance);
    void setGraph2Value(int firstStation, int secondStation, int lengthOfDistance);

    void boxChecking1(int currentIndex);
    void boxChecking2(int currentIndex);

    void searchWay();

private:
    void createNextStation(const QString& stationName, int lengthOfDistance);
    void createPreviousStation(const QString& stationName, int lengthOfDistance);

    void lineItemProcessing(QGraphicsLineItem* item, const Branch& branch);
    void makeDefaultItems();
    void makeClearItems();

    Ui::SubwayMap* ui;
    QGraphicsScene* scene;

    QList<Branch> m_branches;
    QList<QList<Station*>> m_station;
    QList<QStringList> m_stantionsName;
    QList<Junction*> m_junction;

    CreateNewBranchDialog* m_createNewBranchDialog;
    CreateNewStationDialog* m_createNewStationDialog;
    MakeRingOrLineDialog* m_makeRingOrLineDialog;
    CreateJunctionDialog* m_createJunctionDialog;

    int numberOfStations;
    std::vector<std::pair<int, int>> graph1[1000];
    std::vector<std::pair<int, int>> graph2[1000];
};

#endif // SUBWAYMAP_H
