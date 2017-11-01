#include "makeringorlinedialog.h"
#include "ui_makeringorlinedialog.h"

MakeRingOrLineDialog::MakeRingOrLineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MakeRingOrLineDialog){
    ui->setupUi(this);
    this->setModal(true);
    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowSystemMenuHint);
    ui->lengthOfDistance->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9]"), this));

    ui->errorLabel->setText("");
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(dataChecking()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(closeDialog()));
}

void MakeRingOrLineDialog::dataChecking(){
     ui->errorLabel->setText("");
    if (!ui->lengthOfDistance->text().isEmpty()){
        emit makeRingDone(ui->lengthOfDistance->text().toInt());
        this->closeDialog();
    }
    else{
         ui->errorLabel->setText("Ошибка: некорректно введены данные!");
    }
}

void MakeRingOrLineDialog::setStations(const QString& station1, const QString& station2){
    ui->stationLabel1->setText(station1);
    ui->stationLabel2->setText(station2);
}

void MakeRingOrLineDialog::closeDialog(){
    ui->lengthOfDistance->clear();
    this->close();
}

MakeRingOrLineDialog::~MakeRingOrLineDialog(){
    delete ui;
}
