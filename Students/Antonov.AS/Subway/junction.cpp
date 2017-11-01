#include "junction.h"

Junction::Junction(QGraphicsObject *parent) :
    QGraphicsObject(parent){
}

void Junction::setStations(QList<Station*> station){
    m_station = station;
    for (int i = 0; i < station.size(); i++){
        m_station[i]->setPos(this->pos().x(), this->pos().y() + 20 * i);
        m_station[i]->updateLineItems();
    }
}


QRectF Junction::boundingRect() const{
    return QRectF (-10,-10,20, m_station.size() * 20);
}


void Junction::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->save();
    painter->setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawRoundRect(-10,-10, 20, m_station.size() * 20, 50, 50);
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->restore();
}


void Junction::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    this->setPos(mapToScene(event->pos()));
    for (int i = 0; i < m_station.size(); i++){
        QGraphicsSceneMouseEvent *tempEvent = event;
        QPointF pointEvent;
        pointEvent.setX(event->pos().x());
        pointEvent.setY(event->pos().y());
        tempEvent->setPos(pointEvent);
        m_station[i]->mouseMoveEvent(tempEvent);
    }
}

void Junction::mousePressEvent(QGraphicsSceneMouseEvent *event){
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void Junction::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
