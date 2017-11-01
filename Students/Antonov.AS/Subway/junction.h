#ifndef JUNCTION_H
#define JUNCTION_H

#include <QGraphicsObject>
#include "station.h"

class Junction : public QGraphicsObject{
    Q_OBJECT

public:
    explicit Junction(QGraphicsObject *parent = 0);
    void setStations(QList<Station*> station);
private:
    QList<Station*> m_station;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // JUNCTION_H
