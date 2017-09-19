#ifndef FIGURE_H
#define FIGURE_H

#include <QString>

enum Direct{left, right, down};

struct Coordinate{
    Coordinate(){}
    Coordinate(const Coordinate& other) : x(other.x), y(other.y){}
    Coordinate(int _x, int _y) : x(_x), y(_y){}
    Coordinate& operator=(const Coordinate& other);
    friend bool operator==(const Coordinate &left, const Coordinate &right);
    friend bool operator != (const Coordinate &left, const Coordinate &right);
    int x;
    int y;
};

class Figure{
public:
    void setType(const QChar& type);
    void setCoordinates(const Coordinate& coord);

    Coordinate getPoint(int n) const;
    void changePoint(int n, Coordinate coordinate);

    bool isBelong(const Coordinate& coord) const;

    QChar type() const;
    QString icon() const;

private:
    Coordinate m_point[4];
    QChar m_type;
};


#endif // FIGURE_H
