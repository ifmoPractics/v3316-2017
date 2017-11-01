#include "saverecorddialog.h"
#include "ui_saverecorddialog.h"

SaveRecordDialog::SaveRecordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveRecordDialog)
{
    ui->setupUi(this);
    this->setModal(true);
    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowSystemMenuHint);
    ui->nameEdit->setValidator(new QRegExpValidator(QRegExp("[A-Za-z\\d]*"), this));
    ui->nameEdit->setMaxLength(10);

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(saveRecord()));
}

void SaveRecordDialog::saveRecord(){
    if (ui->nameEdit->text() != ""){
        Record record;
        bool isNewRecord = false;
        for (int i = 0; i < 10; i++){
            if (gameSaveController.getRecord(i + 1).score <= ui->scoreResult->text().toInt()){
                record.place = i + 1;
                record.name = ui->nameEdit->text();
                record.score = ui->scoreResult->text().toInt();
                record.line = ui->lineResult->text().toInt();
                isNewRecord = true;
                break;
            }
        }
        if (isNewRecord){
            for (int i = 9; i >= record.place; i--){
                Record oldRecord(gameSaveController.getRecord(i));
                gameSaveController.saveRecord(oldRecord);
            }
            gameSaveController.saveRecord(record);
        }
        this->close();
    }
}

void SaveRecordDialog::setValues(int score, int line){
    ui->scoreResult->setText(QString::number(score));
    ui->lineResult->setText(QString::number(line));
}

SaveRecordDialog::~SaveRecordDialog(){
    delete ui;
}
