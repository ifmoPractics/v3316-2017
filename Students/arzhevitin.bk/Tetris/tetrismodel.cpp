#include "tetrismodel.h"
#include <algorithm>
#include <random>
#include <ctime>

using namespace tetrismodel;

TetrisItem::TetrisItem(const QPoint &point)
    : m_pointOnField(point)
    , m_touchCounter(MAX_TOUCHES_NUMBER)
{

}

TetrisItem TetrisItem::generateRandom()
{
    static QVector<TetrisItem> ITEMS;
    if (ITEMS.isEmpty()) {
        ITEMS = {
            TetrisItem({
                { FCT::E, FCT::E, FCT::I, FCT::E },
                { FCT::E, FCT::E, FCT::I, FCT::E },
                { FCT::E, FCT::E, FCT::I, FCT::E },
                { FCT::E, FCT::E, FCT::I, FCT::E }
            }),
            TetrisItem({
                { FCT::E, FCT::J, FCT::E },
                { FCT::E, FCT::J, FCT::E },
                { FCT::J, FCT::J, FCT::E }
            }),
            TetrisItem({
                { FCT::E, FCT::L, FCT::E },
                { FCT::E, FCT::L, FCT::E },
                { FCT::E, FCT::L, FCT::L }
            }),
            TetrisItem({
                { FCT::O, FCT::O },
                { FCT::O, FCT::O }
            }),
            TetrisItem({
                { FCT::E, FCT::S, FCT::S },
                { FCT::S, FCT::S, FCT::E },
                { FCT::E, FCT::E, FCT::E }
            }),
            TetrisItem({
                { FCT::T, FCT::T, FCT::T },
                { FCT::E, FCT::T, FCT::E },
                { FCT::E, FCT::E, FCT::E }
            }),
            TetrisItem({
                { FCT::Z, FCT::Z, FCT::E },
                { FCT::E, FCT::Z, FCT::Z },
                { FCT::E, FCT::E, FCT::E }
            }),
        };
    }

    shuffle(ITEMS.begin(), ITEMS.end(), std::default_random_engine(time(0)));

    TetrisItem tmp = ITEMS.last();
    ITEMS.pop_back();
    return tmp;
}

FCT TetrisItem::getBlockType(const QPoint &block) const
{
    if ( (block.x() < 0) || (block.x() >= this->getSizeBlocks()) ||
         (block.y() < 0) || (block.y() >= this->getSizeBlocks()) ) {
        return FCT::E;
    }
    return m_itemMatrix[block.y()][block.x()];
}

int TetrisItem::getSizeBlocks() const
{
    return m_itemMatrix.size();
}

void TetrisItem::setPosition(const QPoint &p)
{
    if ((p.x() < 0) && (p.y() < 0)) {
        return;
    }

    m_pointOnField = p;
}

QPoint TetrisItem::getPosition() const
{
    return m_pointOnField;
}

void TetrisItem::rotateClockwise()
{
    Matrix newMatrix = m_itemMatrix;
    for (int i(0); i < this->getSizeBlocks(); ++i){
        for (int j(0); j < this->getSizeBlocks(); ++j){
            newMatrix[j][this->getSizeBlocks() - i - 1] = m_itemMatrix[i][j];
        }
    }
    m_itemMatrix = newMatrix;
}

bool TetrisItem::isNull() const
{
    return m_itemMatrix.isEmpty();
}

bool TetrisItem::isToched()
{
    return (m_touchCounter > 0) ? true : false;
}

int TetrisItem::getTochCount()
{
    return m_touchCounter;
}

void TetrisItem::resetTochCount()
{
    m_touchCounter = MAX_TOUCHES_NUMBER;
}

TetrisItem::TetrisItem(const Matrix &matrix)
    : TetrisItem()
{
    m_itemMatrix = matrix;
}

void TetrisItem::decTouchCounter()
{
    if (this->isToched()) {
        --m_touchCounter;
    }
}


TetrisModel::TetrisModel()
    : m_score(0)
    , m_gameActive(true)
    , m_level(1)

{
    m_fieldMatrix.fill( QVector<FCT>(FIELD_SIZE.width(), FCT::E)
                      , FIELD_SIZE.height() );

    srand( time( 0 ) );
}

FCT TetrisModel::getBlockType(const QPoint &block) const
{
    if ( (block.x() < 0) || (block.x() >= this->getSizeBlocks().width()) ||
         (block.y() < 0) || (block.y() >= this->getSizeBlocks().height())
       ) {
        return FCT::E;
    }
    return m_fieldMatrix[block.y()][block.x()];
}

QSize TetrisModel::getSizeBlocks() const
{
    return QSize(m_fieldMatrix.at(0).size(), m_fieldMatrix.size());
}

bool TetrisModel::hasCollisions(const TetrisItem &item) const
{
    for (int i(0); i < item.getSizeBlocks(); ++i) {
        for (int j(0); j < item.getSizeBlocks(); ++j) {

            int fieldXPoint(item.getPosition().x() + j - 1);
            int fieldYPoint(item.getPosition().y() + i - 1);
            QPoint tryPointItem(j, i);
            QPoint tryPointField(fieldXPoint, fieldYPoint);

            if ( (item.getBlockType(tryPointItem) != FCT::E)
                 &&
                 ( (fieldXPoint < 0) || (fieldYPoint < 0)
                   || (fieldXPoint >= this->getSizeBlocks().width())
                   || (fieldYPoint >= this->getSizeBlocks().height())
                 ) ) {
                return true;
            }
            if ( (item.getBlockType(tryPointItem) != FCT::E) &&
                (this->getBlockType(tryPointField) != FCT::E) ) {
                return true;
            }
        }
    }
    return false;
}

void TetrisModel::moveActiveItemLeft()
{
    this->moveActiveItemX(-1);
}

void TetrisModel::moveActiveItemRight()
{
    this->moveActiveItemX(1);
}

void TetrisModel::moveActiveItemDown()
{
    TetrisItem mItem(m_activeItem);

    QPoint offsetPoint(mItem.getPosition().x(), mItem.getPosition().y() + 1);
    mItem.setPosition(offsetPoint);

    if (!hasCollisions(mItem)) {
        mItem.resetTochCount();
        m_activeItem = mItem;
    } else {
        m_activeItem.decTouchCounter();
    }
}

void TetrisModel::rotateActiveItem()
{
    TetrisItem mItem(m_activeItem);
    mItem.rotateClockwise();

    //Просто развернем, если нет коллизий, применем это положение
    if (!hasCollisions(mItem)) {
        m_activeItem = mItem;
        return;
    }

    QPoint offsetPoint;

    //Попробуем оттолкнуть элемент вправо, чтобы избежать коллизий
    offsetPoint = QPoint(mItem.getPosition().x() + 1, mItem.getPosition().y());
    mItem.setPosition(offsetPoint);
    if (!hasCollisions(mItem)) {
        m_activeItem = mItem;
        return;
    }

    //Если все еще есть коллизия, попробуем теперь оттолкнуть элемент влево
    //с учетом сдвига вправо
    offsetPoint = QPoint(mItem.getPosition().x() - 2, mItem.getPosition().y());
    mItem.setPosition(offsetPoint);
    if (!hasCollisions(mItem)) {
        m_activeItem = mItem;
        return;
    }
}

bool TetrisModel::isGameActive() const
{
    return m_gameActive;
}

TetrisItem TetrisModel::getActiveItem() const
{
    return m_activeItem;
}

int TetrisModel::getScore() const
{
    return m_score;
}

int TetrisModel::getLevel() const
{
    return m_level;
}

void TetrisModel::cleanFullLines()
{
    bool fullLine(true);

    for (int i(this->getSizeBlocks().height() - 1); i >= 0; --i) {
        for (int j(0); j < this->getSizeBlocks().width(); ++j) {
            if (m_fieldMatrix[i][j] == FCT::E) {
                fullLine = false;
                break;
            }
        }

        //Если есть заполненная строка
        if (fullLine) {
            //Удаляем эту строку
            m_fieldMatrix.erase(m_fieldMatrix.begin() + i);
            //Создаем новую строку. Заполняем ее значениями Empty
            QVector< FCT > emptyLine(this->getSizeBlocks().width(), FCT::E);
            //Добавляем наверх поля
            m_fieldMatrix.push_front(emptyLine);

            incScore(FULL_LINE_POINTS_FACTOR);
            ++i;
        }

        fullLine = true;
    }
}

void TetrisModel::incScore(int factor)
{
    static int pointToNextLevel = TO_FIRST_LEVEL_POINTS;
    if (m_score > pointToNextLevel) {
        ++m_level;
        pointToNextLevel *= TO_NEXT_LEVEL_COEF;
    }
    m_score += factor * m_level;
}

void TetrisModel::doStep()
{
    if (m_activeItem.isNull()) {
        m_activeItem = TetrisItem::generateRandom();

        int newXPos = this->getSizeBlocks().width() / 2;
        int newYPos = m_activeItem.getSizeBlocks() / 2;
        m_activeItem.setPosition(QPoint(newXPos, newYPos));

        //Если при генерации нового элемента произошла коллизия
        //свободного места нет -> завершить игру
        if (hasCollisions(m_activeItem)) {
            m_gameActive = false;
            return;
        }
    }

    if (!this->isGameActive()) {
        return;
    }

    this->moveActiveItemDown();

    //Если касания закончились, блокируем
    if (!m_activeItem.isToched()) {
        this->fixItemOnField(m_activeItem);
        this->cleanFullLines();

        this->incScore(SET_ITEM_FACTOR);
        m_activeItem = TetrisItem();
    }
}

void TetrisModel::moveActiveItemX(int offsetPoint)
{
    TetrisItem mItem(m_activeItem);

    QPoint newPos(mItem.getPosition().x() + offsetPoint
                  , mItem.getPosition().y());
    mItem.setPosition(newPos);

    if (!hasCollisions(mItem)) {
        m_activeItem = mItem;
    }
}

void TetrisModel::fixItemOnField(const TetrisItem &item)
{
    for (int i(0); i < item.getSizeBlocks(); ++i) {
        for (int j(0); j < item.getSizeBlocks(); ++j) {
            if (item.getBlockType(QPoint(j,i)) != FCT::E) {

                int fieldXPoint(item.getPosition().x() + j - 1);
                int fieldYPoint(item.getPosition().y() + i - 1);
                m_fieldMatrix[fieldYPoint][fieldXPoint] = item.getBlockType(QPoint(j,i));
            }
        }
    }
}
