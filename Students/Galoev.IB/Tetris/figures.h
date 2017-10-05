#ifndef FIGURES_H
#define FIGURES_H

#include <QPoint>
#include <QDebug>

enum FiguresType { I, J, L, O, S, Z, T, NOFIGURE};

class Figures
{
public:
    Figures(int xPoint = 0, int yPoint = 0);
    void generateFigure(FiguresType type);
    void setPosition(int xPoint, int yPoint);
    void setType(FiguresType type);
    void rotate();
    void moveDown();
    void moveLeft();
    void moveRight();
    FiguresType getType() const;
    QPoint getPoint(int i) const;
    void clear();
    ~Figures();
private:
    QPoint m_points[4];
    FiguresType m_type;
    int m_xPoint;
    int m_yPoint;
    int m_position;
};

#endif // FIGURES_H
