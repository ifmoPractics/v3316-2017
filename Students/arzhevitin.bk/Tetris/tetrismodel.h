/* Файл реализации Модели с логикой
 * и правилами игры
**/

#pragma once

#include <QVector>
#include <QPoint>
#include <QSize>


namespace tetrismodel {
    const int   MAX_TOUCHES_NUMBER      = 2;
    const int   FULL_LINE_POINTS_FACTOR = 10;
    const int   SET_ITEM_FACTOR         = 1;
    const int   SPEED_INCREASE_FACTOR   = 2;
    const int   MAX_SPEED               = 10;
    const int   SPEED                   = 1;
    const int   TO_FIRST_LEVEL_POINTS   = 50;
    const int   TO_NEXT_LEVEL_COEF      = 2;
    const QSize FIELD_SIZE              = QSize(10,25);

    enum class FCT /*FieldCellType*/ {
        E, /*=empty*/
        I, J, L, O, S, T, Z,
    };

    typedef QVector< QVector< FCT > > Matrix;
}

///----------------------------------------------------------------------------
class TetrisItem
{
public:
    TetrisItem(const QPoint &point = QPoint(0,0));
    static TetrisItem generateRandom();

    void    rotateClockwise();
    void    setPosition(const QPoint &p);
    int     getSizeBlocks() const;
    int     getTochCount();
    QPoint  getPosition() const;
    bool    isNull() const;
    bool    isToched();
    void    resetTochCount();
    void    decTouchCounter();
    tetrismodel::FCT getBlockType(const QPoint &block) const; /// <- Извлечение
                        /// типа блока по внутренним координатам матрицы фигуры
private:    
    TetrisItem(const tetrismodel::Matrix &matrix);

    tetrismodel::Matrix m_itemMatrix;
    QPoint              m_pointOnField; //Точка блока на поле
    int                 m_touchCounter;
};


///----------------------------------------------------------------------------
class TetrisModel
{
public:
    TetrisModel();

    void doStep();

    void moveActiveItemLeft();
    void moveActiveItemRight();
    void moveActiveItemDown();
    void rotateActiveItem();

    tetrismodel::FCT getBlockType(const QPoint &block) const;  /// <- Извлечение типа
    QSize            getSizeBlocks() const;             /// блока по внутренним
    TetrisItem       getActiveItem() const;             /// координатам матрицы поля
    int              getScore() const;
    int              getLevel() const;
    bool             isGameActive() const;

private:
    tetrismodel::Matrix m_fieldMatrix;
    TetrisItem          m_activeItem;
    int                 m_score;
    bool                m_gameActive;
    int                 m_level;

private:
    bool hasCollisions(const TetrisItem &item) const;
    void moveActiveItemX(int offsetPoint);
    void fixItemOnField(const TetrisItem& item);
    void cleanFullLines();
    void incScore(int factor);
};
