#include "distance.h"

Distance::Distance()
    : m_lineItem(nullptr), m_length(0){
}

Distance::Distance(QGraphicsLineItem* lineItem, int length)
    : m_lineItem(lineItem), m_length(length){
}

void Distance::setLength(int length){
    m_length = length;
}

int Distance::getLength() const{
    return m_length;
}

void Distance::setLineItem(QGraphicsLineItem *lineItem){
    m_lineItem = lineItem;
}

void Distance::useClearLineItem(){
    m_lineItem->setOpacity(0.1);
}

void Distance::useDefaultLineItem(){
    m_lineItem->setOpacity(1);
}

QGraphicsLineItem* Distance::getLineItem() const{
    return m_lineItem;
}
