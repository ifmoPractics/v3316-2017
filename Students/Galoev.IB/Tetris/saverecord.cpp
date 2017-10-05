#include "saverecord.h"

SaveRecord::SaveRecord(QWidget *parent) : QWidget(parent)
{
    lbl = new QLabel("Введите имя");
    line = new QLineEdit;
    ok = new QPushButton("Ok");
    QHBoxLayout *h_layout = new QHBoxLayout;
    QVBoxLayout *v_layout = new QVBoxLayout;

    h_layout->addWidget(lbl);
    h_layout->addWidget(line);

    v_layout->addLayout(h_layout);
    v_layout->addWidget(ok);

    setLayout(v_layout);
    m_score = -1;

    connect(ok, SIGNAL(clicked(bool)), this, SLOT(okClicked()));
}

void SaveRecord::okClicked(){
    if (line->text().isEmpty())
        QMessageBox::about(0,"Error","Введите ник!");
    else{
        bool flag =false;
        Record rec;
        for (int i = 0; i<5; ++i)
            if(saveParam.loadRecord(i).m_score < m_score){
                rec.m_name=line->text();
                rec.m_score=m_score;
                rec.m_place=i;
                flag = true;
                break;
            }
        for (int i = 4; i>rec.m_place; i--){
            Record rec_move(saveParam.loadRecord(i-1));
            rec_move.m_place++;
            saveParam.saveRecord(rec_move);
        }
        saveParam.saveRecord(rec);
        this->close();
        emit endSaveRecord();

    }

}

void SaveRecord::setScore(int score){
    m_score = score;
}

SaveRecord::~SaveRecord(){
    delete lbl;
    delete line;
    delete ok;
}

