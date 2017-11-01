#include "branch.h"

Branch::Branch(int branchNumber, const QColor &color)
    : m_branchNumber(branchNumber), m_color(color), m_ring(false){
}

void Branch::doRing(){
    m_ring = true;
}

void Branch::doLine(){
    m_ring = false;
}

QColor Branch::getColor() const{
    return m_color;
}

int Branch::getBranchNumber() const{
    return m_branchNumber;
}

bool Branch::isRing() const{
    return m_ring;
}

void Branch::setName(const QString &name){
    m_branchName = name;
}

QString Branch::getName() const{
    return m_branchName;
}
