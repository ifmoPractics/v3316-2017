#include "gamecontroller.h"

GameController::GameController(QWidget *parent) : QFrame(parent){
    srand(time(NULL));
    m_timer = new QTimer;
    m_currentFigure = new Figure;
    m_saveRecordDialog = new SaveRecordDialog;
    nextFigure = new Figure;
    this->createNextFigure();

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            m_matrix[i][j] = new QLabel(this);
        }
    }
    connect(m_timer, SIGNAL(timeout()), this, SLOT(moveFigure()));
}

void GameController::initilizeGame(){
    m_turn = 0;
    m_score = 0;
    m_line = 0;
    emit changeLine(m_line);
    emit changeScore(m_score);
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            m_matrix[i][j]->setPixmap(QPixmap());
            m_matrix[i][j]->setGeometry(j * m_rectSize, i * m_rectSize,
                                        m_rectSize, m_rectSize);
        }
    }
}

SaveParameters GameController::getParameters() const{
    QString matrix[17][10];
    Coordinate coordinate[4];
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            m_matrix[i][j]->pixmap()->isNull() ? matrix[i][j] = "" : matrix[i][j] = m_currentFigure->icon();
        }
    }
    for (int i = 0; i < 4; i++){
        coordinate[i] = m_currentFigure->getPoint(i);
    }
    return SaveParameters(matrix, m_line, m_score, m_currentFigure->type(), coordinate, nextFigure->type());
}

void GameController::setParameters(const SaveParameters& parameters){
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            m_matrix[i][j]->setPixmap(QPixmap(parameters.matrix[i][j]));
            m_matrix[i][j]->setGeometry(j * m_rectSize, i * m_rectSize,
                                        m_rectSize, m_rectSize);
        }
    }
    m_currentFigure->setType(parameters.type);
    nextFigure->setType(parameters.nextType);
    for (int i = 0; i < 4; i++){
        m_currentFigure->changePoint(i, parameters.coordinate[i]);
    }
    m_line = parameters.line;
    m_score = parameters.score;
    emit changeLine(m_line);
    emit changeScore(m_score);
    emit newNextFigure();
}

void GameController::startGame(){
    this->initilizeGame();
    this->getRandomFigure();
    this->buildingFigure();
    this->goGame();
}

bool GameController::lose() const{
    return (!m_matrix[1][5]->pixmap()->isNull());
}

void GameController::moveFigure(){
    if (!this->isCollision(down)){
        this->rebuildingFigure();
        for (int i = 0; i < 4; i++){
            m_currentFigure->changePoint(i, Coordinate(m_currentFigure->getPoint(i).x,
                                         m_currentFigure->getPoint(i).y + 1));
        }
    } else{
        this->deleteLines();

        if (this->lose()){
            this->stopGame();
            for (int i = height - 1; i >= 0 ; i--){
                for (int j = width - 1; j >= 0; j--){
                    m_matrix[i][j]->setPixmap(QPixmap(m_currentFigure->icon()));
                    this->delay(10);
                }
            }
            m_saveRecordDialog->setValues(m_score, m_line);
            m_saveRecordDialog->show();
            emit endGame();
        }

        this->getRandomFigure();
    }
    this->buildingFigure();
}

void GameController::moveFigure(const Direct& direct){
    this->rebuildingFigure();
    switch (direct){
    case right:
        for (int i = 0; i < 4; i++){
            m_currentFigure->changePoint(i, Coordinate(m_currentFigure->getPoint(i).x + 1,
                                         m_currentFigure->getPoint(i).y));
        }
        break;
    case left:
        for (int i = 0; i < 4; i++){
            m_currentFigure->changePoint(i, Coordinate(m_currentFigure->getPoint(i).x - 1,
                                         m_currentFigure->getPoint(i).y));
        }
        break;
    default:
        break;
    }
    this->buildingFigure();
}

void GameController::stopGame(){
    m_timer->stop();
}

void GameController::goGame(){
    this->setFocus();
    m_timer->start(240);
}

void GameController::buildingFigure(){
    for (int i = 0; i < 4; i++){
        m_matrix[m_currentFigure->getPoint(i).y][m_currentFigure->getPoint(i).x]->
                setPixmap(m_currentFigure->icon());
    }
}

void GameController::rebuildingFigure(){
    for (int i = 0; i < 4; i++){
        m_matrix[m_currentFigure->getPoint(i).y][m_currentFigure->getPoint(i).x]->setPixmap(QPixmap());
    }
}

void GameController::createNextFigure(){
    int number(rand() % 7);
    switch (number){
    case 0:
        nextFigure->setType('I');
        break;
    case 1:
        nextFigure->setType('O');;
        break;
    case 2:
        nextFigure->setType('L');
        break;
    case 3:
        nextFigure->setType('J');
        break;
    case 4:
        nextFigure->setType('S');
        break;
    case 5:
        nextFigure->setType('Z');
            break;
    case 6:
        nextFigure->setType('T');
        break;
    default:
        break;
    }
}

void GameController::getRandomFigure(){
    m_turn = 0;
    Coordinate coordinate(5, 1);

    m_currentFigure->setType(nextFigure->type());
    m_currentFigure->setCoordinates(coordinate);
    this->createNextFigure();

    emit newNextFigure();
}

void GameController::turnFigure(){
    this->rebuildingFigure();
    switch (m_currentFigure->type().unicode()){
    case 'I':
        switch (m_turn){
        case 0:
            if ((m_currentFigure->getPoint(1).x < width - 1) && (m_currentFigure->getPoint(1).x > 1)
            && m_matrix[m_currentFigure->getPoint(1).y][m_currentFigure->getPoint(1).x + 1]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y][m_currentFigure->getPoint(1).x - 1]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y][m_currentFigure->getPoint(1).x - 2]->pixmap()->isNull()){
                m_currentFigure->changePoint(0, Coordinate(m_currentFigure->getPoint(1).x + 1, m_currentFigure->getPoint(1).y));
                m_currentFigure->changePoint(2, Coordinate(m_currentFigure->getPoint(1).x - 1, m_currentFigure->getPoint(1).y));
                m_currentFigure->changePoint(3, Coordinate(m_currentFigure->getPoint(1).x - 2, m_currentFigure->getPoint(1).y));
                m_turn++;
            }
            break;  
        case 1:
            if ((m_currentFigure->getPoint(1).y < height - 2)
            && m_matrix[m_currentFigure->getPoint(1).y - 1][m_currentFigure->getPoint(1).x]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y + 1][m_currentFigure->getPoint(1).x]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y + 2][m_currentFigure->getPoint(1).x]->pixmap()->isNull()){
                m_currentFigure->changePoint(0, Coordinate(m_currentFigure->getPoint(1).x, m_currentFigure->getPoint(1).y - 1));
                m_currentFigure->changePoint(2, Coordinate(m_currentFigure->getPoint(1).x, m_currentFigure->getPoint(1).y + 1));
                m_currentFigure->changePoint(3, Coordinate(m_currentFigure->getPoint(1).x, m_currentFigure->getPoint(1).y + 2));
                m_turn++;
            }
            break;
        default:
            break;
        }
        if (m_turn == 2) m_turn = 0;
        break;

    case 'L':
        switch (m_turn){
        case 0:
            if ((m_currentFigure->getPoint(1).x > 0)
            && m_matrix[m_currentFigure->getPoint(1).y][m_currentFigure->getPoint(1).x + 1]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y][m_currentFigure->getPoint(1).x - 1]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y + 1][m_currentFigure->getPoint(1).x - 1]->pixmap()->isNull()){
                m_currentFigure->changePoint(0, Coordinate(m_currentFigure->getPoint(1).x + 1, m_currentFigure->getPoint(1).y));
                m_currentFigure->changePoint(2, Coordinate(m_currentFigure->getPoint(1).x - 1, m_currentFigure->getPoint(1).y));
                m_currentFigure->changePoint(3, Coordinate(m_currentFigure->getPoint(1).x - 1, m_currentFigure->getPoint(1).y + 1));
                m_turn++;
            }
            break;
        case 1:
            if (m_matrix[m_currentFigure->getPoint(1).y + 1][m_currentFigure->getPoint(1).x]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y - 1][m_currentFigure->getPoint(1).x]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y - 1][m_currentFigure->getPoint(1).x - 1]->pixmap()->isNull()){
                m_currentFigure->changePoint(0, Coordinate(m_currentFigure->getPoint(1).x, m_currentFigure->getPoint(1).y + 1));
                m_currentFigure->changePoint(2, Coordinate(m_currentFigure->getPoint(1).x, m_currentFigure->getPoint(1).y - 1));
                m_currentFigure->changePoint(3, Coordinate(m_currentFigure->getPoint(1).x - 1, m_currentFigure->getPoint(1).y - 1));
                m_turn++;
            }
            break;
        case 2:
            if ((m_currentFigure->getPoint(1).x < width - 1)
            && m_matrix[m_currentFigure->getPoint(1).y][m_currentFigure->getPoint(1).x - 1]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y][m_currentFigure->getPoint(1).x + 1]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y - 1][m_currentFigure->getPoint(1).x + 1]->pixmap()->isNull()){
                m_currentFigure->changePoint(0, Coordinate(m_currentFigure->getPoint(1).x - 1, m_currentFigure->getPoint(1).y));
                m_currentFigure->changePoint(2, Coordinate(m_currentFigure->getPoint(1).x + 1, m_currentFigure->getPoint(1).y));
                m_currentFigure->changePoint(3, Coordinate(m_currentFigure->getPoint(1).x + 1, m_currentFigure->getPoint(1).y - 1));
                m_turn++;
            }
            break;
        case 3:
            if ((m_currentFigure->getPoint(1).y < height - 1)
            && m_matrix[m_currentFigure->getPoint(1).y - 1][m_currentFigure->getPoint(1).x]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y + 1][m_currentFigure->getPoint(1).x]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y + 1][m_currentFigure->getPoint(1).x + 1]->pixmap()->isNull()){
                m_currentFigure->changePoint(0, Coordinate(m_currentFigure->getPoint(1).x, m_currentFigure->getPoint(1).y - 1));
                m_currentFigure->changePoint(2, Coordinate(m_currentFigure->getPoint(1).x, m_currentFigure->getPoint(1).y + 1));
                m_currentFigure->changePoint(3, Coordinate(m_currentFigure->getPoint(1).x + 1, m_currentFigure->getPoint(1).y + 1));
                m_turn++;
            }
            break;
        default:
            break;
        }
        if (m_turn == 4) m_turn = 0;
        break;

    case 'J':
        switch (m_turn){
        case 0:
            if ((m_currentFigure->getPoint(1).x < width - 1)
            && m_matrix[m_currentFigure->getPoint(1).y][m_currentFigure->getPoint(1).x + 1]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y][m_currentFigure->getPoint(1).x - 1]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y - 1][m_currentFigure->getPoint(1).x - 1]->pixmap()->isNull()){
                m_currentFigure->changePoint(0, Coordinate(m_currentFigure->getPoint(1).x + 1, m_currentFigure->getPoint(1).y));
                m_currentFigure->changePoint(2, Coordinate(m_currentFigure->getPoint(1).x - 1, m_currentFigure->getPoint(1).y));
                m_currentFigure->changePoint(3, Coordinate(m_currentFigure->getPoint(1).x - 1, m_currentFigure->getPoint(1).y - 1));
                m_turn++;
            }
            break;
        case 1:
            if ((m_currentFigure->getPoint(1).y < height - 1)
            && m_matrix[m_currentFigure->getPoint(1).y + 1][m_currentFigure->getPoint(1).x]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y - 1][m_currentFigure->getPoint(1).x]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y - 1][m_currentFigure->getPoint(1).x + 1]->pixmap()->isNull()){
                m_currentFigure->changePoint(0, Coordinate(m_currentFigure->getPoint(1).x, m_currentFigure->getPoint(1).y + 1));
                m_currentFigure->changePoint(2, Coordinate(m_currentFigure->getPoint(1).x, m_currentFigure->getPoint(1).y - 1));
                m_currentFigure->changePoint(3, Coordinate(m_currentFigure->getPoint(1).x + 1, m_currentFigure->getPoint(1).y - 1));
                m_turn++;
            }
            break;
        case 2:
            if ((m_currentFigure->getPoint(1).x > 0)
            && m_matrix[m_currentFigure->getPoint(1).y][m_currentFigure->getPoint(1).x - 1]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y][m_currentFigure->getPoint(1).x + 1]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y + 1][m_currentFigure->getPoint(1).x + 1]->pixmap()->isNull()){
                m_currentFigure->changePoint(0, Coordinate(m_currentFigure->getPoint(1).x - 1, m_currentFigure->getPoint(1).y));
                m_currentFigure->changePoint(2, Coordinate(m_currentFigure->getPoint(1).x + 1, m_currentFigure->getPoint(1).y));
                m_currentFigure->changePoint(3, Coordinate(m_currentFigure->getPoint(1).x + 1, m_currentFigure->getPoint(1).y + 1));
                m_turn++;
            }
            break;
        case 3:
            if (m_matrix[m_currentFigure->getPoint(1).y - 1][m_currentFigure->getPoint(1).x]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y + 1][m_currentFigure->getPoint(1).x]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y + 1][m_currentFigure->getPoint(1).x - 1]->pixmap()->isNull()){
                m_currentFigure->changePoint(0, Coordinate(m_currentFigure->getPoint(1).x, m_currentFigure->getPoint(1).y - 1));
                m_currentFigure->changePoint(2, Coordinate(m_currentFigure->getPoint(1).x, m_currentFigure->getPoint(1).y + 1));
                m_currentFigure->changePoint(3, Coordinate(m_currentFigure->getPoint(1).x - 1, m_currentFigure->getPoint(1).y + 1));
                m_turn++;
            }
            break;
        default:
            break;
        }
        if (m_turn == 4) m_turn = 0;
        break;

    case 'S':
        switch (m_turn){
        case 0:
            if (m_matrix[m_currentFigure->getPoint(1).y + 1][m_currentFigure->getPoint(1).x]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y][m_currentFigure->getPoint(1).x - 1]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y - 1][m_currentFigure->getPoint(1).x - 1]->pixmap()->isNull()){
                m_currentFigure->changePoint(0, Coordinate(m_currentFigure->getPoint(1).x, m_currentFigure->getPoint(1).y + 1));
                m_currentFigure->changePoint(2, Coordinate(m_currentFigure->getPoint(1).x - 1, m_currentFigure->getPoint(1).y));
                m_currentFigure->changePoint(3, Coordinate(m_currentFigure->getPoint(1).x - 1, m_currentFigure->getPoint(1).y - 1));
                m_turn++;
            }
            break;
        case 1:
            if ((m_currentFigure->getPoint(1).x < width - 1)
            && m_matrix[m_currentFigure->getPoint(1).y][m_currentFigure->getPoint(1).x + 1]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y + 1][m_currentFigure->getPoint(1).x]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y + 1][m_currentFigure->getPoint(1).x - 1]->pixmap()->isNull()){
                m_currentFigure->changePoint(0, Coordinate(m_currentFigure->getPoint(1).x + 1, m_currentFigure->getPoint(1).y));
                m_currentFigure->changePoint(2, Coordinate(m_currentFigure->getPoint(1).x, m_currentFigure->getPoint(1).y + 1));
                m_currentFigure->changePoint(3, Coordinate(m_currentFigure->getPoint(1).x - 1, m_currentFigure->getPoint(1).y + 1));
                m_turn++;
            }
            break;
        default:
            break;
        }
        if (m_turn == 2) m_turn = 0;
        break;

    case 'Z':
        switch (m_turn){
        case 0:
            if (m_matrix[m_currentFigure->getPoint(1).y - 1][m_currentFigure->getPoint(1).x]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y][m_currentFigure->getPoint(1).x - 1]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y + 1][m_currentFigure->getPoint(1).x - 1]->pixmap()->isNull()){
                m_currentFigure->changePoint(0, Coordinate(m_currentFigure->getPoint(1).x, m_currentFigure->getPoint(1).y - 1));
                m_currentFigure->changePoint(2, Coordinate(m_currentFigure->getPoint(1).x - 1, m_currentFigure->getPoint(1).y));
                m_currentFigure->changePoint(3, Coordinate(m_currentFigure->getPoint(1).x - 1, m_currentFigure->getPoint(1).y + 1));
                m_turn++;
            }
            break;
        case 1:
            if ((m_currentFigure->getPoint(1).x < width - 1)
            && m_matrix[m_currentFigure->getPoint(1).y][m_currentFigure->getPoint(1).x - 1]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y + 1][m_currentFigure->getPoint(1).x]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y + 1][m_currentFigure->getPoint(1).x + 1]->pixmap()->isNull()){
                m_currentFigure->changePoint(0, Coordinate(m_currentFigure->getPoint(1).x - 1, m_currentFigure->getPoint(1).y));
                m_currentFigure->changePoint(2, Coordinate(m_currentFigure->getPoint(1).x, m_currentFigure->getPoint(1).y + 1));
                m_currentFigure->changePoint(3, Coordinate(m_currentFigure->getPoint(1).x + 1, m_currentFigure->getPoint(1).y + 1));
                m_turn++;
            }
            break;
        default:
            break;
        }
        if (m_turn == 2) m_turn = 0;
        break;

    case 'T':
        switch (m_turn){
        case 0:
            if ((m_currentFigure->getPoint(1).y < height - 1)
            && m_matrix[m_currentFigure->getPoint(1).y - 1][m_currentFigure->getPoint(1).x]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y + 1][m_currentFigure->getPoint(1).x]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y][m_currentFigure->getPoint(1).x + 1]->pixmap()->isNull()){
                m_currentFigure->changePoint(0, Coordinate(m_currentFigure->getPoint(1).x, m_currentFigure->getPoint(1).y - 1));
                m_currentFigure->changePoint(2, Coordinate(m_currentFigure->getPoint(1).x, m_currentFigure->getPoint(1).y + 1));
                m_currentFigure->changePoint(3, Coordinate(m_currentFigure->getPoint(1).x + 1, m_currentFigure->getPoint(1).y));
                m_turn++;
            }
            break;
        case 1:
            if ((m_currentFigure->getPoint(1).x > 0)
            && m_matrix[m_currentFigure->getPoint(1).y ][m_currentFigure->getPoint(1).x + 1]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y][m_currentFigure->getPoint(1).x - 1]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y + 1][m_currentFigure->getPoint(1).x]->pixmap()->isNull()){
                m_currentFigure->changePoint(0, Coordinate(m_currentFigure->getPoint(1).x + 1, m_currentFigure->getPoint(1).y));
                m_currentFigure->changePoint(2, Coordinate(m_currentFigure->getPoint(1).x - 1, m_currentFigure->getPoint(1).y));
                m_currentFigure->changePoint(3, Coordinate(m_currentFigure->getPoint(1).x, m_currentFigure->getPoint(1).y + 1));
                m_turn++;
            }
            break;
        case 2:
            if (m_matrix[m_currentFigure->getPoint(1).y + 1][m_currentFigure->getPoint(1).x]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y - 1][m_currentFigure->getPoint(1).x]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y][m_currentFigure->getPoint(1).x - 1]->pixmap()->isNull()){
                m_currentFigure->changePoint(0, Coordinate(m_currentFigure->getPoint(1).x, m_currentFigure->getPoint(1).y + 1));
                m_currentFigure->changePoint(2, Coordinate(m_currentFigure->getPoint(1).x, m_currentFigure->getPoint(1).y - 1));
                m_currentFigure->changePoint(3, Coordinate(m_currentFigure->getPoint(1).x - 1, m_currentFigure->getPoint(1).y));
                m_turn++;
            }
            break;
        case 3:
            if ((m_currentFigure->getPoint(1).x < width - 1)
            && m_matrix[m_currentFigure->getPoint(1).y][m_currentFigure->getPoint(1).x - 1]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y][m_currentFigure->getPoint(1).x + 1]->pixmap()->isNull()
            && m_matrix[m_currentFigure->getPoint(1).y - 1][m_currentFigure->getPoint(1).x]->pixmap()->isNull()){
                m_currentFigure->changePoint(0, Coordinate(m_currentFigure->getPoint(1).x - 1, m_currentFigure->getPoint(1).y));
                m_currentFigure->changePoint(2, Coordinate(m_currentFigure->getPoint(1).x + 1, m_currentFigure->getPoint(1).y));
                m_currentFigure->changePoint(3, Coordinate(m_currentFigure->getPoint(1).x, m_currentFigure->getPoint(1).y - 1));
                m_turn++;
            }
            break;
        default:
            break;
        }
        if (m_turn == 4) m_turn = 0;
        break;
    }
    this->buildingFigure();
}

void GameController::deleteLines(){
    int numberOfBlock;
    int i = height - 1;
    int lineCounter = m_line;
    while (i > 0){
        numberOfBlock = 0;
        for (int j = 0; j < width; j++)
            if (!m_matrix[i][j]->pixmap()->isNull()) numberOfBlock++;
            else break;
        if (numberOfBlock == width){
            m_line++;
            emit changeLine(m_line);
            for (int k = i; k > 1; k--)
                for (int j = 0; j < width; j++){
                    QPixmap temporaryPixmap = *m_matrix[k - 1][j]->pixmap();
                    m_matrix[k][j]->setPixmap(temporaryPixmap);
                }
            i++;
            }
        i--;
        }
    lineCounter = m_line - lineCounter;
    if (lineCounter != 0){
        m_score += lineCounter * lineCounter * 10;
        emit changeScore(m_score);
    }
}

void GameController::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_D:
        if (!this->isCollision(right)) this->moveFigure(right);
        break;
    case Qt::Key_A:
        if (!this->isCollision(left)) this->moveFigure(left);
        break;
    case Qt::Key_S:
        if (!this->isCollision(down)) this->moveFigure();
        break;
    case Qt::Key_R:
        this->turnFigure();
        break;
    default:
        break;
    }

}

bool GameController::isCollision(const Direct& direct) const{
    switch (direct){
    case down:
        for (int i = 0; i < 4; i++){
            Coordinate nextPosition(m_currentFigure->getPoint(i).x, m_currentFigure->getPoint(i).y + 1);
            if (m_currentFigure->getPoint(i).y == 16 || (!m_matrix[nextPosition.y][nextPosition.x]->pixmap()->isNull()
                    && !m_currentFigure->isBelong(nextPosition))) return true;
        }
        break;
    case left:
        for (int i = 0; i < 4; i++){
            Coordinate nextPosition(m_currentFigure->getPoint(i).x - 1, m_currentFigure->getPoint(i).y);
            if (m_currentFigure->getPoint(i).x == 0 || (!m_matrix[nextPosition.y][nextPosition.x]->pixmap()->isNull()
                    && !m_currentFigure->isBelong(nextPosition))) return true;
        }
        break;
    case right:
        for (int i = 0; i < 4; i++){
            Coordinate nextPosition(m_currentFigure->getPoint(i).x + 1, m_currentFigure->getPoint(i).y);
            if (m_currentFigure->getPoint(i).x == 9 || (!m_matrix[nextPosition.y][nextPosition.x]->pixmap()->isNull()
                    && !m_currentFigure->isBelong(nextPosition))) return true;
        }
        break;
    }
    return false;
}

void GameController::delay(int millisecondsToWait){
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime ){
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

GameController::~GameController(){
   for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            delete m_matrix[i][j];
        }
    }
   delete m_timer;
   delete m_currentFigure;
   delete m_saveRecordDialog;
   delete nextFigure;
}
