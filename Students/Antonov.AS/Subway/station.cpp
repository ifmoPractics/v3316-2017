#include "station.h"

Station::Station(Branch branch, QString stationName, int stationID, QGraphicsObject *parent) :
    QGraphicsObject(parent), m_branch(branch), m_stationName(stationName), m_stationID(stationID),
    m_distanceToNextStation(nullptr), m_distanceToPreviousStation(nullptr){
}

Station::~Station(){
}

int Station::getID() const{
    return m_stationID;
}

void Station::setStationName(const QString& stationName){
    m_stationName = stationName;
}

void Station::setDistanceToNextStation(Distance *distance){
    m_distanceToNextStation = distance;
}

void Station::setDistanceToPreviousStation(Distance *distance){
    m_distanceToPreviousStation = distance;
}

QString Station::getStationName() const{
    return m_stationName;
}

Distance* Station::getDistanceToNextStation() const{
    return m_distanceToNextStation;
}

Distance* Station::getDistanceToPreviousStation() const{
    return m_distanceToPreviousStation;
}

QRectF Station::boundingRect() const{
    return QRectF (-10,-10,20,20);
}


void Station::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    painter->save();
    if (!clearStation) painter->setOpacity(1);
    else painter->setOpacity(0.1);
    painter->setPen(Qt::black);
    painter->setBrush(m_branch.getColor());
    painter->drawEllipse(-10,-10,20,20);
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->restore();
}

void Station::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    this->setPos(mapToScene(event->pos()));
    this->updateLineItems();
}

void Station::updateLineItems(){
    QGraphicsLineItem* lineItem;

    if (m_distanceToPreviousStation){
        lineItem = m_distanceToPreviousStation->getLineItem();
        lineItem->setLine(QLineF(lineItem->line().p1(), this->pos()));
    }

    if (m_distanceToNextStation){
        lineItem = m_distanceToNextStation->getLineItem();
        lineItem->setLine(QLineF(this->pos(), lineItem->line().p2()));
    }
}

void Station::mousePressEvent(QGraphicsSceneMouseEvent *event){
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void Station::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
