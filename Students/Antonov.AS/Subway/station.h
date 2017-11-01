#ifndef STATION_H
#define STATION_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsObject>
#include <QPainter>
#include <QCursor>

#include "distance.h"
#include "branch.h"

class Station: public QGraphicsObject{
    Q_OBJECT

public:
    Station() = default;
    Station(Branch branch, QString stationName, int stationID, QGraphicsObject *parent = 0);

    void setStationName(const QString& stationName);
    void setDistanceToNextStation(Distance* distance);
    void setDistanceToPreviousStation(Distance* distance);
    int getID() const;
    QString getStationName() const;
    Distance* getDistanceToNextStation() const;
    Distance* getDistanceToPreviousStation() const;
    bool clearStation = false;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void updateLineItems();

    ~Station();
private:
    Branch m_branch;
    QString m_stationName;
    int m_stationID;
    Distance* m_distanceToNextStation;
    Distance* m_distanceToPreviousStation;
};

#endif // STATION_H
