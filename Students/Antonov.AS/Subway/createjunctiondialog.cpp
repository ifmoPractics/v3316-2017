#include "createjunctiondialog.h"
#include "ui_createjunctiondialog.h"

CreateJunctionDialog::CreateJunctionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateJunctionDialog){
    ui->setupUi(this);
    this->setModal(true);
    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowSystemMenuHint);

    ui->lengthOfDistance->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9]"), this));
    ui->lengthOfDistance_2->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9]"), this));
    ui->lengthOfDistance_3->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9]"), this));

    ui->numberOfStationsBox->setCurrentIndex(0);
    ui->branchBox_3->setEnabled(false);
    ui->stationBox_3->setEnabled(false);
    ui->lengthOfDistance_2->setEnabled(false);
    ui->lengthOfDistance_3->setEnabled(false);

    connect(ui->numberOfStationsBox, SIGNAL(currentIndexChanged(int)), this, SLOT(checkingNumberOfStation(int)));

    connect(ui->branchBox_1, SIGNAL(currentIndexChanged(int)), this, SLOT(boxChecking1(int)));
    connect(ui->branchBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(boxChecking2(int)));
    connect(ui->branchBox_3, SIGNAL(currentIndexChanged(int)), this, SLOT(boxChecking3(int)));

    connect(ui->stationBox_1, SIGNAL(currentIndexChanged(int)), this, SLOT(stationChecking1(int)));
    connect(ui->stationBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(stationChecking2(int)));
    connect(ui->stationBox_3, SIGNAL(currentIndexChanged(int)), this, SLOT(stationChecking3(int)));

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(dataChecking()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(closeDialog()));
}

void CreateJunctionDialog::checkingNumberOfStation(int number){
    if (number == 0){
        ui->branchBox_3->setEnabled(false);
        ui->stationBox_3->setEnabled(false);
        ui->lengthOfDistance_2->setEnabled(false);
        ui->lengthOfDistance_3->setEnabled(false);
    }
    else {
        ui->branchBox_3->setEnabled(true);
        ui->stationBox_3->setEnabled(true);
        ui->lengthOfDistance_2->setEnabled(true);
        ui->lengthOfDistance_3->setEnabled(true);
    }
}

void CreateJunctionDialog::setNewBranch(const QString& branchName){
    m_stantionsName.push_back(QStringList());
    ui->branchBox_1->addItem(branchName);
    ui->branchBox_2->addItem(branchName);
    ui->branchBox_3->addItem(branchName);
}

void CreateJunctionDialog::setNewStation(int branchNumber, bool isNextStation, const QString& stationName){
    if (isNextStation) m_stantionsName[branchNumber].push_back(stationName);
    else m_stantionsName[branchNumber].push_front(stationName);
    emit ui->branchBox_1->currentIndexChanged(0);
    emit ui->branchBox_2->currentIndexChanged(0);
    emit ui->branchBox_3->currentIndexChanged(0);
}

void CreateJunctionDialog::boxChecking1(int currentIndex){
    ui->stationBox_1->clear();
    ui->stationBox_1->addItems(m_stantionsName[currentIndex]);
    ui->stationLabel1->setText(ui->stationBox_1->currentText());
    ui->stationLabel1_3->setText(ui->stationBox_1->currentText());
}

void CreateJunctionDialog::boxChecking2(int currentIndex){
    ui->stationBox_2->clear();
    ui->stationBox_2->addItems(m_stantionsName[currentIndex]);
    ui->stationLabel2->setText(ui->stationBox_2->currentText());
    ui->stationLabel1_2->setText(ui->stationBox_2->currentText());
}

void CreateJunctionDialog::boxChecking3(int currentIndex){
    ui->stationBox_3->clear();
    ui->stationBox_3->addItems(m_stantionsName[currentIndex]);
    ui->stationLabel2_2->setText(ui->stationBox_3->currentText());
    ui->stationLabel2_3->setText(ui->stationBox_3->currentText());
}

void CreateJunctionDialog::stationChecking1(int){
    ui->stationLabel1->setText(ui->stationBox_1->currentText());
    ui->stationLabel1_3->setText(ui->stationBox_1->currentText());
}

void CreateJunctionDialog::stationChecking2(int){
    ui->stationLabel2->setText(ui->stationBox_2->currentText());
    ui->stationLabel1_2->setText(ui->stationBox_2->currentText());
}

void CreateJunctionDialog::stationChecking3(int){
    ui->stationLabel2_2->setText(ui->stationBox_3->currentText());
    ui->stationLabel2_3->setText(ui->stationBox_3->currentText());
}

void CreateJunctionDialog::dataChecking(){
    QList<QPair<int, int> > indexesOfStations;
    indexesOfStations.push_back(QPair<int, int>(ui->branchBox_1->currentIndex(), ui->stationBox_1->currentIndex()));
    indexesOfStations.push_back(QPair<int, int>(ui->branchBox_2->currentIndex(), ui->stationBox_2->currentIndex()));
    if (ui->branchBox_3->isEnabled())
        indexesOfStations.push_back(QPair<int, int>(ui->branchBox_3->currentIndex(), ui->stationBox_3->currentIndex()));

    bool error = false;
    QString errorMessage = "";
    ui->errorLabel->setText(errorMessage);

    for (int i = 0; i < indexesOfStations.size(); i++){
        for (int j = 0; j < m_usedStations.size(); j++){
            if (indexesOfStations[i] == m_usedStations[j]){
                error = true;
                errorMessage = "Ошибка: Станции уже использованы!";
            }
        }
    }

    if (ui->branchBox_1->currentIndex() == ui->branchBox_2->currentIndex()){
        error = true;
        errorMessage = "Ошибка: станции не могут быть одной ветки!";
    }
    if (ui->numberOfStationsBox->currentIndex() == 1){
        if (ui->branchBox_2->currentIndex() == ui->branchBox_3->currentIndex()
                || ui->branchBox_1->currentIndex() == ui->branchBox_3->currentIndex()){
            error = true;
            errorMessage = "Ошибка: станции не могут быть одной ветки!";
        }
    }

    if (ui->lengthOfDistance->text().isEmpty()){
        error = true;
        errorMessage = "Ошибка: некорректно введены данные!";
    }
    if (ui->numberOfStationsBox->currentIndex() == 1){
        if (ui->lengthOfDistance_2->text().isEmpty() || ui->lengthOfDistance_3->text().isEmpty()){
            error = true;
            errorMessage = "Ошибка: некорректно введены данные!";
        }
    }

    ui->errorLabel->setText(errorMessage);

    if (!error){
        QList<int> m_junctionLengths;
        m_junctionLengths.push_back(ui->lengthOfDistance->text().toInt());
        if (ui->numberOfStationsBox->currentIndex() == 1){
            m_junctionLengths.push_back(ui->lengthOfDistance_2->text().toInt());
            m_junctionLengths.push_back(ui->lengthOfDistance_3->text().toInt());
        }

        for (int i = 0; i < indexesOfStations.size(); i++)
            m_usedStations.push_back(indexesOfStations[i]);
        emit junctionInitialized(indexesOfStations, m_junctionLengths);
        this->closeDialog();
    }
}

void CreateJunctionDialog::closeDialog(){
    ui->branchBox_1->setCurrentIndex(0);
    ui->branchBox_2->setCurrentIndex(0);
    ui->branchBox_3->setCurrentIndex(0);
    this->close();
}

CreateJunctionDialog::~CreateJunctionDialog(){
    delete ui;
}
