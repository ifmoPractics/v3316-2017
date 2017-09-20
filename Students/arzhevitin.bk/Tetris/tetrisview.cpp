#include "tetrisview.h"


TetrisView::TetrisView(QWidget *parent)
    : QWidget(parent)
{
    this->loadPictures();

    m_scoreLcd = new QLCDNumber();
    m_scoreLcd->setFixedSize(120,60);
    m_levelLcd = new QLCDNumber();
    m_levelLcd->setFixedSize(120,60);
    m_gameField = new QWidget();
    m_gameField->setFixedSize(MAX_GAME_FIELD_SIZE);
    QLabel *lblLevel = new QLabel("Level");
    QLabel *lblScore = new QLabel("Score");
    QHBoxLayout *hLayout = new QHBoxLayout();
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(lblLevel);
    vLayout->addWidget(m_levelLcd);
    vLayout->addWidget(lblScore);
    vLayout->addWidget(m_scoreLcd);
    vLayout->addStretch();
    hLayout->addLayout(vLayout);
    hLayout->addWidget(m_gameField);
    this->setLayout(hLayout);

    m_tetrisController = new TetrisController(&m_tetrisModel, this);
    connect(m_tetrisController, SIGNAL(doRefresh()), SLOT(repaint()));
    connect(m_tetrisController, SIGNAL(gameOver()), SIGNAL(gameOver()));


    ///вычисляем размер клетки
    m_boxSize = floor(m_gameField->minimumSize().height() / m_tetrisModel.getSizeBlocks().height());

    //создаем массив картинок для поля
    for (int i = 0; i < m_tetrisModel.getSizeBlocks().height(); ++i) {
        QVector<QLabel*> temp;
        for (int j = 0; j < m_tetrisModel.getSizeBlocks().width(); ++j) {
            QLabel* plbl = new QLabel(m_gameField);
            plbl->setPixmap(QPixmap(""));
            plbl->setGeometry(j*m_boxSize, i*m_boxSize, m_boxSize, m_boxSize);
            plbl->setScaledContents(true);

            temp.push_back(plbl);
        }
        m_imgField.push_back(temp);
    }

    this->repaint();
}

TetrisView::~TetrisView() {
}

void TetrisView::pauseGame()
{

}

void TetrisView::exitGame()
{

}

void TetrisView::paintEvent(QPaintEvent *)
{   
    ///Перерисовка поля
    QSize fieldSizeBlocks = m_tetrisModel.getSizeBlocks();

    for (int i = 0; i < fieldSizeBlocks.height(); ++i) {
        for (int j = 0; j < fieldSizeBlocks.width(); ++j) {            
            tetrismodel::FCT type = m_tetrisModel.getBlockType(QPoint(j,i));
            m_imgField[i][j]->setPixmap(getPixmap(type));
        }
    }

    TetrisItem activeItem = m_tetrisModel.getActiveItem();
    bool isAlmostUnouched = (activeItem.getTochCount() < tetrismodel::MAX_TOUCHES_NUMBER);


    for (int i = 0; i < activeItem.getSizeBlocks(); ++i) {
        for (int j = 0; j < activeItem.getSizeBlocks(); ++j) {
            int fJ(activeItem.getPosition().x() + j - 1);
            int fI(activeItem.getPosition().y() + i - 1);

            tetrismodel::FCT type = activeItem.getBlockType(QPoint(j,i));
            if (type != tetrismodel::FCT::E) {
                m_imgField[fI][fJ]->setPixmap(getPixmap(type));
            }

            if ((activeItem.getBlockType(QPoint(j,i)) != tetrismodel::FCT::E) && isAlmostUnouched) {
                QPixmap *lessOpasity = const_cast<QPixmap *>(m_imgField[fI][fJ]->pixmap());
                lessOpasity->fill(Qt::gray);
            }
        }
    }
    m_levelLcd->display(m_tetrisModel.getLevel());
    m_scoreLcd->display(m_tetrisModel.getScore());
}

void TetrisView::keyPressEvent(QKeyEvent *pe)
{
    switch(pe->key()) {
    case Qt::Key_Up :
    case Qt::Key_W : {
        m_tetrisController->rotateItem();
        break;
    }
    case Qt::Key_Down :
    case Qt::Key_S : {
        m_tetrisController->enableAccelerate(true);
        break;
    }
    case Qt::Key_Left :
    case Qt::Key_A : {
        m_tetrisController->moveItemleft();
        break;
    }
    case Qt::Key_Right :
    case Qt::Key_D : {
        m_tetrisController->moveItemRight();
        break;
    }
    case Qt::Key_Backspace : {
        m_tetrisController->pause();
    }
    default:
        QWidget::keyPressEvent(pe);
    }
}

void TetrisView::keyReleaseEvent(QKeyEvent *pe)
{
    switch(pe->key()){
    case Qt::Key_Down :
    case Qt::Key_S : {
        m_tetrisController->enableAccelerate(false);
        break;
    }
    default:
        QWidget::keyPressEvent(pe);
    }
}

void TetrisView::loadPictures()
{
    img_i = QPixmap(":/img/block_i.png");
    img_j = QPixmap(":/img/block_j.png");
    img_l = QPixmap(":/img/block_l.png");
    img_o = QPixmap(":/img/block_o.png");
    img_s = QPixmap(":/img/block_s.png");
    img_t = QPixmap(":/img/block_t.png");
    img_z = QPixmap(":/img/block_z.png");
}

QPixmap TetrisView::getPixmap(tetrismodel::FCT type)
{
    switch (type) {
    case tetrismodel::FCT::I : return img_i;
    case tetrismodel::FCT::J : return img_j;
    case tetrismodel::FCT::L : return img_l;
    case tetrismodel::FCT::O : return img_o;
    case tetrismodel::FCT::S : return img_s;
    case tetrismodel::FCT::T : return img_t;
    case tetrismodel::FCT::Z : return img_z;
    default: return QPixmap();
    }
}
