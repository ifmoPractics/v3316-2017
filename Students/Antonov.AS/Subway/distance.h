#ifndef DISTANCE_H
#define DISTANCE_H

#include <QObject>
#include <QGraphicsLineItem>

class Distance :public QObject, public QGraphicsLineItem{
    Q_OBJECT

public:
    Distance();
    Distance(QGraphicsLineItem* lineItem, int length);
    void setLength(int length);
    int getLength() const;

    void setLineItem(QGraphicsLineItem* lineItem);
    QGraphicsLineItem* getLineItem() const;

    void useDefaultLineItem();
    void useClearLineItem();
private:
    QGraphicsLineItem* m_lineItem;
    int m_length;
};

#endif // DISTANCE_H
