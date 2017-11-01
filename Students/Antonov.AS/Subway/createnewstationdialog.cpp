#include "createnewstationdialog.h"
#include "ui_createnewstationdialog.h"

CreateNewStationDialog::CreateNewStationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateNewStationDialog){
    ui->setupUi(this);
    this->setModal(true);
    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowSystemMenuHint);
    ui->stationName->setMaxLength(20);
    ui->stationName->setValidator(new QRegExpValidator(QRegExp("[a-zA-Zа-яА-Я0-9 ]+"), this));
    ui->lengthOfDistance->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9]"), this));

    ui->errorLabel->setText("");
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(dataChecking()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(closeDialog()));
}

void CreateNewStationDialog::dataChecking(){
    ui->errorLabel->setText("");
    if (!ui->stationName->text().isEmpty() && !ui->lengthOfDistance->text().isEmpty()){
        emit stationInitialized(ui->nextStation->isChecked(),
                                ui->stationName->text(), ui->lengthOfDistance->text().toInt());
        this->closeDialog();
    }
    else{
        ui->errorLabel->setText("Ошибка: некорректно введены данные!");
    }
}

void CreateNewStationDialog::closeDialog(){
    ui->stationName->clear();
    ui->lengthOfDistance->clear();
    this->close();
}

CreateNewStationDialog::~CreateNewStationDialog(){
    delete ui;
}
