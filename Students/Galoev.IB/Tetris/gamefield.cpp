#include "gamefield.h"

GameField::GameField(int width, int height, QWidget *parent) :
    QWidget(parent), m_width(width), m_height(height), m_speed(16), m_score(0), m_gameOver(false), m_num_cur(0)
{
    //m_score = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerend()));
    timer->start(INTERVAL);

    m_num_next = rand()%7;
    m_field.resize(m_height);
    for (int i=0; i<m_height; ++i)
        m_field[i].resize(m_width);
    //timerid = startTimer(INTERVAL);
    this->resize(m_width*BLOCK_SIZE+1, m_height*BLOCK_SIZE+1);
    srand(time(0));
}

void GameField::moveFigureDown(){
    if(curFigure.getType() == NOFIGURE){
        m_num_cur = m_num_next;
        m_num_next = rand()%7;
        emit changedNextFigure(m_num_next);
        curFigure.generateFigure(FiguresType(m_num_cur));
        Figures checkFigure = curFigure;
        checkFigure.setPosition(FIELD_WIDTH/2-2, 0);
        if (!checkCollisions(checkFigure)){
            curFigure.setPosition(FIELD_WIDTH/2-2, 0);
            writeFigure();
        } else {
            //killTimer(timerid);
            timer->stop();
            m_gameOver = true;
            saveGame();
            emit endGame(m_score);
            update();
        }
    }else{
        Figures checkFigure = curFigure;
        checkFigure.moveDown();
        if (!checkCollisions(checkFigure)){
            clearFigure();
            curFigure.moveDown();
            writeFigure();
        } else{
            emit changedNextFigure(m_num_next);
            curFigure.clear();
            deleteFullLine();
        }
    }
}

void GameField::moveFigureLeft(){
    Figures checkFigure = curFigure;
    checkFigure.moveLeft();
    if(!checkCollisions(checkFigure)){
        clearFigure();
        curFigure.moveLeft();
        writeFigure();
        update();
    }
}

void GameField::moveFigureRight(){
    Figures checkFigure = curFigure;
    checkFigure.moveRight();
    if(!checkCollisions(checkFigure)){
        clearFigure();
        curFigure.moveRight();
        writeFigure();
        update();
    }
}

void GameField::rotateFigure(){
    Figures checkFigure = curFigure;
    checkFigure.rotate();
    if(!checkCollisions(checkFigure)){
        clearFigure();
        curFigure.rotate();
        writeFigure();
        update();
    }
}
/*
void GameField::timerEvent(QTimerEvent *event){
    Q_UNUSED(event);
    moveFigureDown();
    update();
}*/

void GameField::timerend(){
    moveFigureDown();
    update();
}

void GameField::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    QBrush brush;
    for (int i=0; i<m_height; i++){
        for (int j=0; j<m_width; j++){
            if (m_gameOver)
                brush = Qt::NoBrush;
            else{
                switch (m_field[i][j]) {
                case 0:
                    brush = Qt::NoBrush;
                    break;
                case 1:
                    brush = Qt::blue;
                    break;
                case 2:
                    brush = Qt::darkBlue;
                    break;
                case 3:
                    brush = Qt::darkYellow;
                    break;
                case 4:
                    brush = Qt::yellow;
                    break;
                case 5:
                    brush = Qt::green;
                    break;
                case 6:
                    brush = Qt::red;
                    break;
                case 7:
                    brush = Qt::magenta;
                    break;
                }
            }
            painter.setBrush(brush);
            painter.drawRect(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
        }
    }
}

void GameField::writeFigure(){
    for (int i=0; i<4; i++)
        switch (curFigure.getType()) {
        case I:
            m_field[curFigure.getPoint(i).y()][curFigure.getPoint(i).x()] = 1;
            break;
        case J:
            m_field[curFigure.getPoint(i).y()][curFigure.getPoint(i).x()] = 2;
            break;
        case L:
            m_field[curFigure.getPoint(i).y()][curFigure.getPoint(i).x()] = 3;
            break;
        case O:
            m_field[curFigure.getPoint(i).y()][curFigure.getPoint(i).x()] = 4;
            break;
        case S:
            m_field[curFigure.getPoint(i).y()][curFigure.getPoint(i).x()] = 5;
            break;
        case Z:
            m_field[curFigure.getPoint(i).y()][curFigure.getPoint(i).x()] = 6;
            break;
        case T:
            m_field[curFigure.getPoint(i).y()][curFigure.getPoint(i).x()] = 7;
            break;
        }
}

void GameField::clearFigure(){
    for (int i=0; i<4; i++)
        m_field[curFigure.getPoint(i).y()][curFigure.getPoint(i).x()] = 0;
}

void GameField::key_event(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Left:
        //clearFigure();
        //curFigure.moveLeft();
        moveFigureLeft();
        break;
    case Qt::Key_Right:
        //clearFigure();
        //curFigure.moveRight();
        moveFigureRight();
        break;
    case Qt::Key_Up:
        rotateFigure();
        //clearFigure();
        //curFigure.rotate();
        break;
    case Qt::Key_Down:
        moveFigureDown();
        update();
        break;
    }
}

bool GameField::checkCollisions(Figures& figure){
    for (int i=0; i<4; i++){
        if ((figure.getPoint(i).y()<0) || (figure.getPoint(i).y()>=m_height))
            return true;
        if ((figure.getPoint(i).x()<0) || (figure.getPoint(i).x()>=m_width))
            return true;
        bool flagCross=true;
        for (int j=0; j<4; j++)
            if ((figure.getPoint(i) == curFigure.getPoint(j))){
                flagCross=false;
            }
        if ((m_field[figure.getPoint(i).y()][figure.getPoint(i).x()] != 0) && flagCross)
            return true;
    }
    return false;
}

void GameField::deleteFullLine(){
    for (int i=m_height-1; i>=0; --i){
        int count=0;
        for (int j=0; j<m_width; ++j)
            if (m_field[i][j] != 0)
                count++;
        if (count == m_width){
            for (int k=i; k>0; --k)
                for (int l=0; l<m_width; ++l)
                    m_field[k][l]=m_field[k-1][l];
            for (int k=0; k<m_width; ++k)
                m_field[0][k]=0;
            ++i;
            m_score++;
            emit changedScore(m_score);
        }
    }
}

void GameField::initGame(){
    curFigure.clear();
    m_speed = 16;
    m_score = 0;
    m_gameOver = false;
    for (int i=0; i<m_height; ++i)
        for (int j=0; j<m_width; ++j)
            m_field[i][j] = 0;
    //timerid = startTimer(INTERVAL);
    timer->start(INTERVAL);
    m_num_cur=0;
    m_num_next=rand()%7;
}

void GameField::saveGame(){
    clearFigure();
    Parametrs param(m_field, m_score, m_num_cur, m_num_next, m_gameOver);
    saveParam.saveGame(param);
}

void GameField::resumeGame(){
    Parametrs param;
    param = saveParam.loadGame();
    curFigure.clear();
    m_speed = 16;
    m_score = param.m_score;
    m_gameOver = param.m_gameOver;
    m_field = param.m_field;
    //timerid = startTimer(INTERVAL);
    timer->start(INTERVAL);
    m_num_cur = param.m_num_cur;
    m_num_next = param.m_num_next;

    curFigure.setType(FiguresType(m_num_cur));
    emit changedNextFigure(m_num_next);
    Figures checkFigure = curFigure;
    checkFigure.setPosition(FIELD_WIDTH/2-2, 0);
    if (!checkCollisions(checkFigure)){
        curFigure.setPosition(FIELD_WIDTH/2-2, 0);
        writeFigure();
    } else {
        //killTimer(timerid);
        timer->stop();
        m_gameOver = true;
        saveGame();
        emit endGame(m_score);
        update();
    }
}


