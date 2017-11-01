#include "createnewbranchdialog.h"
#include "ui_createnewbranchdialog.h"

CreateNewBranchDialog::CreateNewBranchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateNewBranchDialog){
    ui->setupUi(this);
    this->setModal(true);
    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowSystemMenuHint);
    ui->branchName->setMaxLength(20);
    ui->firstStationName->setMaxLength(20);
    ui->branchName->setValidator(new QRegExpValidator(QRegExp("[a-zA-Zа-яА-Я0-9 ]+"), this));
    ui->firstStationName->setValidator(new QRegExpValidator(QRegExp("[a-zA-Zа-яА-Я0-9 ]+"), this));
    ui->r->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9][0-9]"), this));
    ui->g->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9][0-9]"), this));
    ui->b->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9][0-9]"), this));

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(dataChecking()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(closeDialog()));

    ui->errorLabel->setText("");
}

void CreateNewBranchDialog::dataChecking(){
    ui->errorLabel->setText("");
    if ((ui->r->text().toInt() > 255) || (ui->g->text().toInt() > 255) || (ui->b->text().toInt() > 255)){
       ui->errorLabel->setText("Ошибка: значение RGB не может превышать 255!");
    }
    else if (!ui->branchName->text().isEmpty() && !ui->firstStationName->text().isEmpty()
            && !ui->r->text().isEmpty() && !ui->g->text().isEmpty() && !ui->b->text().isEmpty()){
        emit branchInitialized(ui->branchName->text(), ui->firstStationName->text(),
                               QColor(ui->r->text().toInt(), ui->g->text().toInt(), ui->b->text().toInt()));
        this->closeDialog();
    }
    else{
        ui->errorLabel->setText("Ошибка: некорректно введены данные!");
    }
}

void CreateNewBranchDialog::closeDialog(){
    ui->branchName->clear();
    ui->firstStationName->clear();
    ui->r->clear();
    ui->g->clear();
    ui->b->clear();
    this->close();
}

CreateNewBranchDialog::~CreateNewBranchDialog(){
    delete ui;
}
