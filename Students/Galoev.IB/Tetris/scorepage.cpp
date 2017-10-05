#include "scorepage.h"

ScorePage::ScorePage(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    button_ok = new QPushButton("OK");
    for (int i=0; i<5; i++){
        m_labels[i]= new QLabel(this);
        layout->addWidget(m_labels[i]);
    }
    layout->addWidget(button_ok);
    setLayout(layout);

    connect(button_ok, SIGNAL(clicked(bool)), this, SIGNAL(closeScorePage()));
}

void ScorePage::loadRecords(){
    for (int i=0; i<5; i++){
        m_labels[i]->setText(QString::number(saveParam.loadRecord(i).m_place+1) + "."+saveParam.loadRecord(i).m_name+":"+QString::number(saveParam.loadRecord(i).m_score));
    }
}
