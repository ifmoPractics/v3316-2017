#include "figures.h"

Figures::Figures(int xPoint, int yPoint) :
    m_xPoint(xPoint), m_yPoint(yPoint), m_type(NOFIGURE)
{
   // for(int i=0; i<4; i++)
   //     m_points[i](0,0);
    m_type = NOFIGURE;
}

void Figures::generateFigure(FiguresType type){
    m_type = type;
    switch (m_type) {
    case I:
        //m_points[0](m_xPoint, m_yPoint);
        m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint);
        //m_points[1](m_xPoint+1, m_yPoint);
        m_points[1].setX(m_xPoint+1); m_points[1].setY(m_yPoint);
        //m_points[2](m_xPoint+2, m_yPoint);
        m_points[2].setX(m_xPoint+2); m_points[2].setY(m_yPoint);
        //m_points[3](m_xPoint+3, m_yPoint);
        m_points[3].setX(m_xPoint+3); m_points[3].setY(m_yPoint);
        break;
    case J:
        //m_points[0](m_xPoint, m_yPoint);
        m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint);
        //m_points[1](m_xPoint, m_yPoint+1);
        m_points[1].setX(m_xPoint); m_points[1].setY(m_yPoint+1);
        //m_points[2](m_xPoint+1, m_yPoint+1);
        m_points[2].setX(m_xPoint+1); m_points[2].setY(m_yPoint+1);
        //m_points[3](m_xPoint+2, m_yPoint+1);
        m_points[3].setX(m_xPoint+2); m_points[3].setY(m_yPoint+1);
        break;
    case L:
        //m_points[0](m_xPoint, m_yPoint+1);
        m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint+1);
        //m_points[1](m_xPoint+1, m_yPoint+1);
        m_points[1].setX(m_xPoint+1); m_points[1].setY(m_yPoint+1);
        //m_points[2](m_xPoint+2, m_yPoint+1);
        m_points[2].setX(m_xPoint+2); m_points[2].setY(m_yPoint+1);
        //m_points[3](m_xPoint+2, m_yPoint);
        m_points[3].setX(m_xPoint+2); m_points[3].setY(m_yPoint);
        break;
    case O:
        //m_points[0](m_xPoint, m_yPoint);
        m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint);
        //m_points[1](m_xPoint, m_yPoint+1);
        m_points[1].setX(m_xPoint); m_points[1].setY(m_yPoint+1);
        //m_points[2](m_xPoint+1, m_yPoint);
        m_points[2].setX(m_xPoint+1); m_points[2].setY(m_yPoint);
        //m_points[3](m_xPoint+1, m_yPoint+1);
        m_points[3].setX(m_xPoint+1); m_points[3].setY(m_yPoint+1);
        break;
    case S:
        //m_points[0](m_xPoint, m_yPoint+1);
        m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint+1);
        //m_points[1](m_xPoint+1, m_yPoint+1);
        m_points[1].setX(m_xPoint+1); m_points[1].setY(m_yPoint+1);
        //m_points[2](m_xPoint+1, m_yPoint);
        m_points[2].setX(m_xPoint+1); m_points[2].setY(m_yPoint);
        //m_points[3](m_xPoint+2, m_yPoint);
        m_points[3].setX(m_xPoint+2); m_points[3].setY(m_yPoint);
        break;
    case Z:
        //m_points[0](m_xPoint, m_yPoint);
        m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint);
        //m_points[1](m_xPoint+1, m_yPoint);
        m_points[1].setX(m_xPoint+1); m_points[1].setY(m_yPoint);
        //m_points[2](m_xPoint+1, m_yPoint+1);
        m_points[2].setX(m_xPoint+1); m_points[2].setY(m_yPoint+1);
        //m_points[3](m_xPoint+2, m_yPoint+1);
        m_points[3].setX(m_xPoint+2); m_points[3].setY(m_yPoint+1);
        break;
    case T:
        //m_points[0](m_xPoint, m_yPoint);
        m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint+1);
        //m_points[1](m_xPoint+1, m_yPoint);
        m_points[1].setX(m_xPoint+1); m_points[1].setY(m_yPoint+1);
        //m_points[2](m_xPoint+1, m_yPoint+1);
        m_points[2].setX(m_xPoint+1); m_points[2].setY(m_yPoint);
        //m_points[3](m_xPoint+2, m_yPoint+1);
        m_points[3].setX(m_xPoint+2); m_points[3].setY(m_yPoint+1);
        break;
    case NOFIGURE:
        //m_points[0](0, 0);
        m_points[0].setX(0); m_points[0].setY(0);
        //m_points[1](0, 0);
        m_points[1].setX(0); m_points[1].setY(0);
        //m_points[2](0, 0);
        m_points[2].setX(0); m_points[2].setY(0);
        //m_points[3](0, 0);
        m_points[3].setX(0); m_points[3].setY(0);
        break;
    }
}

void Figures::rotate(){
    m_position ++;
    m_position %= 4;
    switch (m_type) {
    case I:
        switch (m_position) {
        case 0:
        case 2:
            m_xPoint--;
            //m_yPoint++;
            //m_points[0](m_xPoint, m_yPoint);
            m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint);
            //m_points[1](m_xPoint+1, m_yPoint);
            m_points[1].setX(m_xPoint+1); m_points[1].setY(m_yPoint);
            //m_points[2](m_xPoint+2, m_yPoint);
            m_points[2].setX(m_xPoint+2); m_points[2].setY(m_yPoint);
            //m_points[3](m_xPoint+3, m_yPoint);
            m_points[3].setX(m_xPoint+3); m_points[3].setY(m_yPoint);
            break;
        case 1:
        case 3:
            m_xPoint++;
            m_yPoint--;
            //m_points[0](m_xPoint, m_yPoint);
            m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint);
            //m_points[1](m_xPoint, m_yPoint+1);
            m_points[1].setX(m_xPoint); m_points[1].setY(m_yPoint+1);
            //m_points[2](m_xPoint, m_yPoint+2);
            m_points[2].setX(m_xPoint); m_points[2].setY(m_yPoint+2);
            //m_points[3](m_xPoint, m_yPoint+3);
            m_points[3].setX(m_xPoint); m_points[3].setY(m_yPoint+3);
            break;
        }
        break;
    case J:
        switch (m_position) {
        case 0:
            m_xPoint--;
            //m_points[0](m_xPoint, m_yPoint);
            m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint);
            //m_points[1](m_xPoint, m_yPoint+1);
            m_points[1].setX(m_xPoint); m_points[1].setY(m_yPoint+1);
            //m_points[2](m_xPoint+1, m_yPoint+1);
            m_points[2].setX(m_xPoint+1); m_points[2].setY(m_yPoint+1);
            //m_points[3](m_xPoint+2, m_yPoint+1);
            m_points[3].setX(m_xPoint+2); m_points[3].setY(m_yPoint+1);
            break;
        case 1:
            //m_points[0](m_xPoint+1, m_yPoint);
            m_points[0].setX(m_xPoint+1); m_points[0].setY(m_yPoint);
            //m_points[1](m_xPoint, m_yPoint);
            m_points[1].setX(m_xPoint); m_points[1].setY(m_yPoint);
            //m_points[2](m_xPoint, m_yPoint+1);
            m_points[2].setX(m_xPoint); m_points[2].setY(m_yPoint+1);
            //m_points[3](m_xPoint, m_yPoint+2);
            m_points[3].setX(m_xPoint); m_points[3].setY(m_yPoint+2);
            break;
        case 2:
            //m_points[0](m_xPoint, m_yPoint);
            m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint);
            //m_points[1](m_xPoint+1, m_yPoint);
            m_points[1].setX(m_xPoint+1); m_points[1].setY(m_yPoint);
            //m_points[2](m_xPoint+2, m_yPoint);
            m_points[2].setX(m_xPoint+2); m_points[2].setY(m_yPoint);
            //m_points[3](m_xPoint+2, m_yPoint+1);
            m_points[3].setX(m_xPoint+2); m_points[3].setY(m_yPoint+1);
            break;
        case 3:
            m_xPoint++;
            //m_points[0](m_xPoint, m_yPoint);
            m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint);
            //m_points[1](m_xPoint, m_yPoint+1);
            m_points[1].setX(m_xPoint); m_points[1].setY(m_yPoint+1);
            //m_points[2](m_xPoint, m_yPoint+2);
            m_points[2].setX(m_xPoint); m_points[2].setY(m_yPoint+2);
            //m_points[3](m_xPoint+1, m_yPoint+2);
            m_points[3].setX(m_xPoint-1); m_points[3].setY(m_yPoint+2);
            break;
        }
        break;
    case L:
        switch (m_position) {
        case 0:
            //m_yPoint--;
            //m_points[0](m_xPoint, m_yPoint);
            m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint);
            //m_points[1](m_xPoint+1, m_yPoint);
            m_points[1].setX(m_xPoint+1); m_points[1].setY(m_yPoint);
            //m_points[2](m_xPoint+2, m_yPoint);
            m_points[2].setX(m_xPoint+2); m_points[2].setY(m_yPoint);
            //m_points[3](m_xPoint+2, m_yPoint+1);
            m_points[3].setX(m_xPoint+2); m_points[3].setY(m_yPoint-1);
            break;
        case 1:
            m_yPoint -= 2;
            //m_points[0](m_xPoint, m_yPoint);
            m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint);
            //m_points[1](m_xPoint, m_yPoint+1);
            m_points[1].setX(m_xPoint); m_points[1].setY(m_yPoint+1);
            //m_points[2](m_xPoint, m_yPoint+2);
            m_points[2].setX(m_xPoint); m_points[2].setY(m_yPoint+2);
            //m_points[3](m_xPoint+1, m_yPoint+2);
            m_points[3].setX(m_xPoint+1); m_points[3].setY(m_yPoint+2);
            break;
        case 2:
            //m_points[0](m_xPoint, m_yPoint);
            m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint);
            //m_points[1](m_xPoint, m_yPoint+1);
            m_points[1].setX(m_xPoint); m_points[1].setY(m_yPoint+1);
            //m_points[2](m_xPoint+1, m_yPoint);
            m_points[2].setX(m_xPoint+1); m_points[2].setY(m_yPoint);
            //m_points[3](m_xPoint+2, m_yPoint);
            m_points[3].setX(m_xPoint+2); m_points[3].setY(m_yPoint);
            break;
        case 3:
            m_yPoint--;
            //m_points[0](m_xPoint, m_yPoint);
            m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint);
            //m_points[1](m_xPoint+1, m_yPoint);
            m_points[1].setX(m_xPoint+1); m_points[1].setY(m_yPoint);
            //m_points[2](m_xPoint+1, m_yPoint+1);
            m_points[2].setX(m_xPoint+1); m_points[2].setY(m_yPoint+1);
            //m_points[3](m_xPoint+1, m_yPoint+2);
            m_points[3].setX(m_xPoint+1); m_points[3].setY(m_yPoint+2);
            break;
        }
        break;
    case S:
        switch (m_position) {
        case 0:
        case 2:
            //m_points[0](m_xPoint, m_yPoint+1);
            m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint+1);
            //m_points[1](m_xPoint+1, m_yPoint+1);
            m_points[1].setX(m_xPoint+1); m_points[1].setY(m_yPoint+1);
            //m_points[2](m_xPoint+1, m_yPoint);
            m_points[2].setX(m_xPoint+1); m_points[2].setY(m_yPoint);
            //m_points[3](m_xPoint+2, m_yPoint);
            m_points[3].setX(m_xPoint+2); m_points[3].setY(m_yPoint);
            break;
        case 1:
        case 3:
            //m_points[0](m_xPoint, m_yPoint);
            m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint);
            //m_points[1](m_xPoint, m_yPoint+1);
            m_points[1].setX(m_xPoint); m_points[1].setY(m_yPoint+1);
            //m_points[2](m_xPoint+1, m_yPoint+1);
            m_points[2].setX(m_xPoint+1); m_points[2].setY(m_yPoint+1);
            //m_points[3](m_xPoint+1, m_yPoint+2);
            m_points[3].setX(m_xPoint+1); m_points[3].setY(m_yPoint+2);
            break;
        }
        break;
    case Z:
        switch (m_position) {
        case 0:
        case 2:
            //m_points[0](m_xPoint, m_yPoint);
            m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint);
            //m_points[1](m_xPoint+1, m_yPoint);
            m_points[1].setX(m_xPoint+1); m_points[1].setY(m_yPoint);
            //m_points[2](m_xPoint+1, m_yPoint+1);
            m_points[2].setX(m_xPoint+1); m_points[2].setY(m_yPoint+1);
            //m_points[3](m_xPoint+2, m_yPoint+1);
            m_points[3].setX(m_xPoint+2); m_points[3].setY(m_yPoint+1);
            break;
        case 1:
        case 3:
            m_yPoint--;
            //m_points[0](m_xPoint+1, m_yPoint);
            m_points[0].setX(m_xPoint+1); m_points[0].setY(m_yPoint);
            //m_points[1](m_xPoint+1, m_yPoint+1);
            m_points[1].setX(m_xPoint+1); m_points[1].setY(m_yPoint+1);
            //m_points[2](m_xPoint, m_yPoint+1);
            m_points[2].setX(m_xPoint); m_points[2].setY(m_yPoint+1);
            //m_points[3](m_xPoint, m_yPoint+2);
            m_points[3].setX(m_xPoint); m_points[3].setY(m_yPoint+2);
            break;
        }
        break;
    case T:
        switch (m_position) {
        case 0:
            m_xPoint--;
            //m_points[0](m_xPoint, m_yPoint);
            m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint+1);
            //m_points[1](m_xPoint+1, m_yPoint+1);
            m_points[1].setX(m_xPoint+1); m_points[1].setY(m_yPoint+1);
            //m_points[2](m_xPoint+2, m_yPoint+1);
            m_points[2].setX(m_xPoint+2); m_points[2].setY(m_yPoint+1);
            //m_points[3](m_xPoint+1, m_yPoint);
            m_points[3].setX(m_xPoint+1); m_points[3].setY(m_yPoint);
            break;
        case 1:
            //m_points[0](m_xPoint+1, m_yPoint);
            m_points[0].setX(m_xPoint+1); m_points[0].setY(m_yPoint);
            //m_points[1](m_xPoint+1, m_yPoint+1);
            m_points[1].setX(m_xPoint+1); m_points[1].setY(m_yPoint+1);
            //m_points[2](m_xPoint+1, m_yPoint+2);
            m_points[2].setX(m_xPoint+1); m_points[2].setY(m_yPoint+2);
            //m_points[3](m_xPoint, m_yPoint+1);
            m_points[3].setX(m_xPoint); m_points[3].setY(m_yPoint+1);
            break;
        case 2:
            //m_points[0](m_xPoint, m_yPoint);
            m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint);
            //m_points[1](m_xPoint+1, m_yPoint);
            m_points[1].setX(m_xPoint+1); m_points[1].setY(m_yPoint);
            //m_points[2](m_xPoint+2, m_yPoint);
            m_points[2].setX(m_xPoint+2); m_points[2].setY(m_yPoint);
            //m_points[3](m_xPoint+1, m_yPoint+1);
            m_points[3].setX(m_xPoint+1); m_points[3].setY(m_yPoint+1);
            break;
        case 3:
            m_xPoint++;
            //m_points[0](m_xPoint, m_yPoint);
            m_points[0].setX(m_xPoint); m_points[0].setY(m_yPoint);
            //m_points[1](m_xPoint, m_yPoint+1);
            m_points[1].setX(m_xPoint); m_points[1].setY(m_yPoint+1);
            //m_points[2](m_xPoint, m_yPoint+2);
            m_points[2].setX(m_xPoint); m_points[2].setY(m_yPoint+2);
            //m_points[3](m_xPoint+1, m_yPoint+1);
            m_points[3].setX(m_xPoint+1); m_points[3].setY(m_yPoint+1);
            break;
        }
        break;
    }
}

void Figures::moveDown(){
    for (int i=0; i<4; ++i)
        m_points[i].ry()++;
    m_yPoint++;
}

void Figures::moveLeft(){
    for (int i=0; i<4; ++i)
        m_points[i].rx()--;
    m_xPoint--;
}

void Figures::moveRight(){
    for (int i=0; i<4; ++i)
        m_points[i].rx()++;
    m_xPoint++;
}

FiguresType Figures::getType() const{
    return m_type;
}

void Figures::setPosition(int xPoint, int yPoint){
    m_xPoint = xPoint;
    m_yPoint = yPoint;
    generateFigure(m_type);
}

void Figures::setType(FiguresType type){
    m_type=type;
}

QPoint Figures::getPoint(int i) const{
    return m_points[i];
}

void Figures::clear(){
    m_type = NOFIGURE;
    m_xPoint = 0;
    m_yPoint = 0;
    m_position = 0;
    for (int i=0; i<4; i++){
        m_points[i].setX(0);
        m_points[i].setY(0);
    }
}

Figures::~Figures()
{

}
