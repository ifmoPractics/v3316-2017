#include "figure.h"

Coordinate& Coordinate::operator=(const Coordinate& other){
    if (this != &other){
        this->x = other.x;
        this->y = other.y;
    }
    return *this;
}

bool operator==(const Coordinate &left, const Coordinate &right){
    if ((left.x == right.x) && (left.y == right.y)) return true;
    return false;
}

bool operator != (const Coordinate &left, const Coordinate &right){
    return !(left == right);
}

void Figure::setType(const QChar& type){
    m_type = type;
}

void Figure::setCoordinates(const Coordinate& coord){
    switch (m_type.unicode()){
    case 'I':
        m_point[0] = coord;
        m_point[1].x = coord.x;     m_point[1].y = coord.y + 1;
        m_point[2].x = coord.x;     m_point[2].y = coord.y + 2;
        m_point[3].x = coord.x;     m_point[3].y = coord.y + 3;
        break;
    case 'O':
        m_point[0] = coord;
        m_point[1].x = coord.x + 1; m_point[1].y = coord.y;
        m_point[2].x = coord.x + 1; m_point[2].y = coord.y + 1;
        m_point[3].x = coord.x;     m_point[3].y = coord.y + 1;
        break;
    case 'L':
        m_point[0] = coord;
        m_point[1].x = coord.x;     m_point[1].y = coord.y + 1;
        m_point[2].x = coord.x;     m_point[2].y = coord.y + 2;
        m_point[3].x = coord.x + 1; m_point[3].y = coord.y + 2;
        break;
    case 'J':
        m_point[0] = coord;
        m_point[1].x = coord.x;     m_point[1].y = coord.y + 1;
        m_point[2].x = coord.x;     m_point[2].y = coord.y + 2;
        m_point[3].x = coord.x - 1; m_point[3].y = coord.y + 2;
        break;
    case 'S':
        m_point[0] = coord;
        m_point[1].x = coord.x + 1; m_point[1].y = coord.y;
        m_point[2].x = coord.x;     m_point[2].y = coord.y + 1;
        m_point[3].x = coord.x - 1; m_point[3].y = coord.y + 1;
        break;
    case 'Z':
        m_point[0] = coord;
        m_point[1].x = coord.x + 1; m_point[1].y = coord.y;
        m_point[2].x = coord.x + 1; m_point[2].y = coord.y + 1;
        m_point[3].x = coord.x + 2; m_point[3].y = coord.y + 1;
        break;
    case 'T':
        m_point[3] = coord;
        m_point[0].x = coord.x - 1; m_point[0].y = coord.y + 1;
        m_point[1].x = coord.x;     m_point[1].y = coord.y + 1;
        m_point[2].x = coord.x + 1; m_point[2].y = coord.y + 1;
        break;
    default:
        break;
    }
}

bool Figure::isBelong(const Coordinate& coord) const{
    for (int i = 0; i < 4; i++){
        if (m_point[i] == coord) return true;
    }
    return false;
}

void Figure::changePoint(int n, Coordinate coordinate){
    m_point[n] = coordinate;
}

Coordinate Figure::getPoint(int n) const{
    return m_point[n];
}

QChar Figure::type() const{
    return m_type;
}

QString Figure::icon() const{
    return ":/Textures/white.ico";
}
