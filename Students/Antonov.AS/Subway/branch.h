#ifndef BRANCH_H
#define BRANCH_H

#include <QColor>

class Branch{
public:
    Branch() = default;
    Branch(int branchNumber, const QColor& color);

    void doRing();
    void doLine();

    void setName(const QString& name);

    QString getName() const;
    QColor getColor() const;
    int getBranchNumber() const;
    bool isRing() const;

private:
    QString m_branchName;
    int m_branchNumber;
    QColor m_color;
    bool m_ring;
};

#endif // BRANCH_H
