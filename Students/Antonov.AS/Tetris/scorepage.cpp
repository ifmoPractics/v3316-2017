#include "scorepage.h"
#include "ui_scorepage.h"

ScorePage::ScorePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScorePage)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowSystemMenuHint);

    m_labels[0] = ui->place1; m_labels[1] = ui->place2;
    m_labels[2] = ui->place3; m_labels[3] = ui->place4;
    m_labels[4] = ui->place5; m_labels[5] = ui->place6;
    m_labels[6] = ui->place7; m_labels[7] = ui->place8;
    m_labels[8] = ui->place9; m_labels[9] = ui->place10;

    connect(ui->backButton, SIGNAL(clicked()), this, SIGNAL(closeScorePage()));
    connect(ui->refreshButton, SIGNAL(clicked()), this, SLOT(refreshRecords()));
}

void ScorePage::loadRecords(){
    for (int i = 0; i < 10; i++){
        m_labels[i]->setText(QString::number(gameSaveController.getRecord(i + 1).place)
                             + ". " + gameSaveController.getRecord(i + 1).name
                             + " (score: " + QString::number(gameSaveController.getRecord(i + 1).score)
                             + ", line: " + QString::number(gameSaveController.getRecord(i + 1).line)+ ")");
    }
}

void ScorePage::refreshRecords(){
    gameSaveController.refreshRecords();
    this->loadRecords();
}

ScorePage::~ScorePage(){
    delete ui;
}
