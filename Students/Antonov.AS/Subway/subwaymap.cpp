#include "subwaymap.h"
#include "ui_subwaymap.h"

#include <QLineF>
#include <QPointF>
#include <queue>
#include <functional>
#include <algorithm>

SubwayMap::SubwayMap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubwayMap){
    ui->setupUi(this);

    QFile file(":/style.qss");
    if(file.open(QFile::ReadOnly)) {
       QString StyleSheet = QLatin1String(file.readAll());
       qApp->setStyleSheet(StyleSheet);
    }

    this->setFixedSize(this->size());

    numberOfStations = 0;
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    m_makeRingOrLineDialog = new MakeRingOrLineDialog();
    m_createNewBranchDialog = new CreateNewBranchDialog();
    m_createNewStationDialog = new CreateNewStationDialog();
    m_createJunctionDialog = new CreateJunctionDialog();

    ui->makeRingButton->setEnabled(false);
    ui->tabWidget->setTabEnabled(1, false);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    scene->setSceneRect(0, 0, ui->graphicsView->width() - 2, ui->graphicsView->height() - 2);

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),this, SLOT(checkBranchForEnabledMakeRingButton()));
    connect(ui->createButton, SIGNAL(clicked()), m_createNewBranchDialog, SLOT(show()));
    connect(m_createNewBranchDialog, SIGNAL(branchInitialized(QString,QString,QColor)),
            this, SLOT(createStation(QString,QString,QColor)));

    connect(ui->createNewStationButton, SIGNAL(clicked()), m_createNewStationDialog, SLOT(show()));
    connect(m_createNewStationDialog, SIGNAL(stationInitialized(bool,QString,int)),
         this, SLOT(addStation(bool,QString,int)));

    connect(ui->makeRingButton, SIGNAL(clicked()), this, SLOT(showMakeRingDialog()));
    connect(m_makeRingOrLineDialog, SIGNAL(makeRingDone(int)), this, SLOT(makeRing(int)));

    connect(ui->createJunctionButton, SIGNAL(clicked()), m_createJunctionDialog, SLOT(show()));
    connect(m_createJunctionDialog, SIGNAL(junctionInitialized(QList<QPair<int,int> >, QList<int>)),
         this, SLOT(createJunction(QList<QPair<int,int> >, QList<int>)));

    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(swapPanel(int)));

    connect(ui->branchBox_1, SIGNAL(currentIndexChanged(int)), this, SLOT(boxChecking1(int)));
    connect(ui->branchBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(boxChecking2(int)));

    connect(ui->findTheWayButton, SIGNAL(clicked()), this, SLOT(searchWay()));
}

void SubwayMap::boxChecking1(int currentIndex){
    ui->stationBox_1->clear();
    ui->stationBox_1->addItems(m_stantionsName[currentIndex]);
}

void SubwayMap::boxChecking2(int currentIndex){
    ui->stationBox_2->clear();
    ui->stationBox_2->addItems(m_stantionsName[currentIndex]);
}

void SubwayMap::setGraphValue(int firstStation, int secondStation, int lengthOfDistance){
    graph1[firstStation].push_back(std::make_pair(secondStation, lengthOfDistance));
    graph1[secondStation].push_back(std::make_pair(firstStation, lengthOfDistance));
}

void SubwayMap::setGraph2Value(int firstStation, int secondStation, int lengthOfDistance){
    graph2[firstStation].push_back(std::make_pair(secondStation, lengthOfDistance));
    graph2[secondStation].push_back(std::make_pair(firstStation, lengthOfDistance));
}

void SubwayMap::swapPanel(int index){
    if (index == 1){
        ui->graphicsView->setEnabled(false);
    }
    else{
        ui->graphicsView->setEnabled(true);
        ui->notWayLabel->setText("");
        ui->searchTypeBox->setCurrentIndex(0);
        ui->lengthLabel->setText("Время в пути: 0");
        this->makeDefaultItems();
    }
}

void SubwayMap::makeDefaultItems(){
    for (int i = 0; i < m_station.size(); i++){
        for (int j = 0; j < m_station[i].size(); j++){
            m_station[i][j]->clearStation = false;
            if (m_station[i][j]->getDistanceToNextStation() != nullptr)
                m_station[i][j]->getDistanceToNextStation()->useDefaultLineItem();
            if (m_station[i][j]->getDistanceToPreviousStation() != nullptr)
                m_station[i][j]->getDistanceToPreviousStation()->useDefaultLineItem();
        }
    }
}

void SubwayMap::makeClearItems(){
    for (int i = 0; i < m_station.size(); i++){
        for (int j = 0; j < m_station[i].size(); j++){
            m_station[i][j]->clearStation = true;
            if (m_station[i][j]->getDistanceToNextStation() != nullptr)
                m_station[i][j]->getDistanceToNextStation()->useClearLineItem();
            if (m_station[i][j]->getDistanceToPreviousStation() != nullptr)
                m_station[i][j]->getDistanceToPreviousStation()->useClearLineItem();
            m_station[i][j]->update(m_station[i][j]->boundingRect());
        }
    }
}

void SubwayMap::createJunction(const QList<QPair<int,int>>& indexesOfStations, const QList<int>& junctionLengths) {
    Junction* junction = new Junction();
    junction->setPos(300, 250);
    scene->addItem(junction);
    QList<Station*> stationList;
    for (int i = 0; i < indexesOfStations.size(); i++){
        stationList.push_back(m_station[indexesOfStations[i].first][indexesOfStations[i].second]);
    }
    junction->setStations(stationList);
    m_junction.push_back(junction);

    this->setGraphValue(m_station[indexesOfStations[0].first][indexesOfStations[0].second]->getID(),
            m_station[indexesOfStations[1].first][indexesOfStations[1].second]->getID(), junctionLengths[0]);
    this->setGraph2Value(m_station[indexesOfStations[0].first][indexesOfStations[0].second]->getID(),
            m_station[indexesOfStations[1].first][indexesOfStations[1].second]->getID(), 10000);
    if (indexesOfStations.size() == 3){
        this->setGraphValue(m_station[indexesOfStations[1].first][indexesOfStations[1].second]->getID(),
                m_station[indexesOfStations[2].first][indexesOfStations[2].second]->getID(), junctionLengths[1]);
        this->setGraphValue(m_station[indexesOfStations[0].first][indexesOfStations[0].second]->getID(),
                m_station[indexesOfStations[2].first][indexesOfStations[2].second]->getID(), junctionLengths[2]);
        this->setGraph2Value(m_station[indexesOfStations[1].first][indexesOfStations[1].second]->getID(),
                m_station[indexesOfStations[2].first][indexesOfStations[2].second]->getID(), 10000);
        this->setGraph2Value(m_station[indexesOfStations[0].first][indexesOfStations[0].second]->getID(),
                m_station[indexesOfStations[2].first][indexesOfStations[2].second]->getID(), 10000);
    }
}

void SubwayMap::checkBranchForEnabledMakeRingButton(){
    int currentIndex = ui->comboBox->currentIndex();
    if (m_branches.size() >= currentIndex + 1){
        if (m_branches[currentIndex].isRing()){
            ui->makeRingButton->setEnabled(false);
            ui->createNewStationButton->setEnabled(false);
        }
        else{
            ui->createNewStationButton->setEnabled(true);
            if (m_station[currentIndex].size() >= 3){
                ui->makeRingButton->setEnabled(true);
            }
            else {
                ui->makeRingButton->setEnabled(false);
            }
        }
    }
}

void SubwayMap::showMakeRingDialog(){
    m_makeRingOrLineDialog->setStations(m_station[ui->comboBox->currentIndex()].first()->getStationName(),
            m_station[ui->comboBox->currentIndex()].last()->getStationName());
    m_makeRingOrLineDialog->show();
}

void SubwayMap::lineItemProcessing(QGraphicsLineItem *item, const Branch &branch){
    item->setZValue(-1);
    item->setPen(QPen(QBrush(branch.getColor()), 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    scene->addItem(item);
}

void SubwayMap::makeRing(int lengthOfDistance){
    Branch branch(ui->comboBox->currentIndex(), m_branches[ui->comboBox->currentIndex()].getColor());
    m_branches[ui->comboBox->currentIndex()].doRing();

    ui->makeRingButton->setEnabled(false);
    ui->createNewStationButton->setEnabled(false);

    QGraphicsLineItem* lineItem = new QGraphicsLineItem(QLineF(m_station[branch.getBranchNumber()].last()->pos(),
                                                        m_station[branch.getBranchNumber()].first()->pos()));
    this->lineItemProcessing(lineItem, branch);

    this->setGraphValue(m_station[branch.getBranchNumber()].last()->getID(),
            m_station[branch.getBranchNumber()].first()->getID(), lengthOfDistance);
    this->setGraph2Value(m_station[branch.getBranchNumber()].last()->getID(),
            m_station[branch.getBranchNumber()].first()->getID(), 1);

    Distance* distance = new Distance(lineItem, lengthOfDistance);
    m_station[branch.getBranchNumber()].last()->setDistanceToNextStation(distance);
    m_station[branch.getBranchNumber()].first()->setDistanceToPreviousStation(distance);
}

void SubwayMap::createStation(const QString &branchName, const QString &firstStationName, const QColor &color){
    ui->comboBox->addItem(branchName);
    m_branches.push_back(Branch(m_branches.size(), color));
    m_branches.last().doLine();
    m_branches.last().setName(branchName);
    if (m_branches.size() == 2) ui->createJunctionButton->setEnabled(true);
    m_createJunctionDialog->setNewBranch(branchName);
    m_createJunctionDialog->setNewStation(m_branches.last().getBranchNumber(), true, firstStationName);
    m_stantionsName.push_back(QStringList());
    m_stantionsName[m_branches.last().getBranchNumber()].push_back(firstStationName);
    ui->branchBox_1->addItem(branchName);
    ui->branchBox_2->addItem(branchName);
    emit ui->branchBox_1->currentIndexChanged(0);
    emit ui->branchBox_2->currentIndexChanged(0);

    Station *item = new Station(m_branches.last(), firstStationName, numberOfStations++);

    m_station.push_back(QList<Station*>());
    m_station[m_branches.last().getBranchNumber()].push_back(item);
    item->setPos(300, 250);
    scene->addItem(item);

    QGraphicsTextItem *qwe = new QGraphicsTextItem(firstStationName, item);
    qwe->setFont(QFont(".", 9, 190, false));
    qwe->setPos(8, 1);

    ui->comboBox->setEnabled(true);
    ui->comboBox->setCurrentIndex(m_branches.size() - 1);
    this->checkBranchForEnabledMakeRingButton();
    ui->tabWidget->setTabEnabled(1, true);
}

void SubwayMap::addStation(bool isNextStation, const QString &stationName, int lengthOfDistance){
    if (isNextStation){
        this->createNextStation(stationName, lengthOfDistance);
    }
    else{
        this->createPreviousStation(stationName, lengthOfDistance);
    }
    this->checkBranchForEnabledMakeRingButton();
}

void SubwayMap::createNextStation(const QString& stationName, int lengthOfDistance){
    Branch branch = m_branches[ui->comboBox->currentIndex()];
    m_createJunctionDialog->setNewStation(branch.getBranchNumber(), true, stationName);
    m_stantionsName[branch.getBranchNumber()].push_back(stationName);
    emit ui->branchBox_1->currentIndexChanged(0);
    emit ui->branchBox_2->currentIndexChanged(0);
    Station *item = new Station(branch, stationName, numberOfStations++);

    item->setPos(m_station[branch.getBranchNumber()].last()->pos().x() + 75,
            m_station[branch.getBranchNumber()].last()->pos().y());
    scene->addItem(item);

    QGraphicsLineItem* lineItem = new QGraphicsLineItem(QLineF(m_station[branch.getBranchNumber()].last()->pos(),
                                                        item->pos()));
    this->lineItemProcessing(lineItem, branch);

    QGraphicsTextItem *qwe = new QGraphicsTextItem(stationName, item);
    qwe->setFont(QFont(".", 9, 190, false));
    qwe->setPos(8, 1);

    this->setGraphValue(m_station[branch.getBranchNumber()].last()->getID(),
            item->getID(), lengthOfDistance);
    this->setGraph2Value(m_station[branch.getBranchNumber()].last()->getID(),
            item->getID(), 1);

    Distance* distance = new Distance(lineItem, lengthOfDistance);
    m_station[branch.getBranchNumber()].last()->setDistanceToNextStation(distance);
    m_station[branch.getBranchNumber()].push_back(item);
    m_station[branch.getBranchNumber()].last()->setDistanceToPreviousStation(distance);
}

void SubwayMap::createPreviousStation(const QString& stationName, int lengthOfDistance){
    Branch branch = m_branches[ui->comboBox->currentIndex()];
    m_createJunctionDialog->setNewStation(branch.getBranchNumber(), false, stationName);
    m_stantionsName[branch.getBranchNumber()].push_front(stationName);
    emit ui->branchBox_1->currentIndexChanged(0);
    emit ui->branchBox_2->currentIndexChanged(0);
    Station *item = new Station(branch, stationName, numberOfStations++);

    item->setPos(m_station[branch.getBranchNumber()].first()->pos().x() - 75,
            m_station[branch.getBranchNumber()].first()->pos().y());
    scene->addItem(item);

    QGraphicsLineItem* lineItem = new QGraphicsLineItem(QLineF(item->pos(),
                                                               m_station[branch.getBranchNumber()].first()->pos()));
    this->lineItemProcessing(lineItem, branch);

    QGraphicsTextItem *qwe = new QGraphicsTextItem(stationName, item);
    qwe->setFont(QFont(".", 9, 190, false));
    qwe->setPos(8, 1);

    this->setGraphValue(m_station[branch.getBranchNumber()].first()->getID(),
            item->getID(), lengthOfDistance);
    this->setGraph2Value(m_station[branch.getBranchNumber()].first()->getID(),
            item->getID(), 1);

    Distance* distance = new Distance(lineItem, lengthOfDistance);
    m_station[branch.getBranchNumber()].first()->setDistanceToPreviousStation(distance);
    m_station[branch.getBranchNumber()].push_front(item);
    m_station[branch.getBranchNumber()].first()->setDistanceToNextStation(distance);
}

void SubwayMap::searchWay(){
    const int INF = 1e9 + 7;
    int ans[1000];
    int previous[1000];
    int start = m_station[ui->branchBox_1->currentIndex()][ui->stationBox_1->currentIndex()]->getID();
    int end =  m_station[ui->branchBox_2->currentIndex()][ui->stationBox_2->currentIndex()]->getID();

    for (int i = 0; i < numberOfStations; i++) {
        ans[i] = INF;
        previous[i] = -1;
    }

    ans[start] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
    std::greater<std::pair<int, int>>> queue;

    queue.push({ 0, start });

    while (!queue.empty()) {
        std::pair<int, int> c = queue.top();
        queue.pop();

        int dst = c.first, v = c.second;
        if (ans[v] < dst) continue;

        if (ui->searchTypeBox->currentIndex() == 0){
            for (std::pair<int, int> e : graph1[v]) {
                int u = e.first, len_vu = e.second;
                int n_dst = dst + len_vu;
                if (n_dst < ans[u]) {
                    ans[u] = n_dst;
                    previous[u] = v;
                    queue.push({ n_dst, u });
                }
            }
        }
        else{
            for (std::pair<int, int> e : graph2[v]) {
                int u = e.first, len_vu = e.second;
                int n_dst = dst + len_vu;
                if (n_dst < ans[u]) {
                    ans[u] = n_dst;
                    previous[u] = v;
                    queue.push({ n_dst, u });
                }
            }
        }
    }

    std::vector<int> path;
    int cur = end;
    path.push_back(cur);

    while (previous[cur] != -1) {
        cur = previous[cur];
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());


    std::vector<int>::iterator it;
    Station* previousStation = new Station();
    Station* startStation = nullptr;
    Station* endStation = nullptr;

    this->makeClearItems();
    for (int i = 0; i < m_station.size(); i++){
        for (int j = 0; j < m_station[i].size(); j++){
            it = std::find(path.begin(), path.end(), m_station[i][j]->getID());
            if (it != path.end()){
                m_station[i][j]->clearStation = false;
                if (previousStation->getDistanceToNextStation() != nullptr && m_station[i][j]->getDistanceToPreviousStation() != nullptr){
                    if (previousStation->getDistanceToNextStation() == m_station[i][j]->getDistanceToPreviousStation()){
                        m_station[i][j]->getDistanceToPreviousStation()->useDefaultLineItem();
                    }
                }
                if (previousStation->getDistanceToPreviousStation() != nullptr && m_station[i][j]->getDistanceToNextStation() != nullptr){
                    if (previousStation->getDistanceToPreviousStation() == m_station[i][j]->getDistanceToNextStation()){
                        previousStation->getDistanceToPreviousStation()->useDefaultLineItem();
                    }
                }
                if (!startStation) startStation = m_station[i][j];
                previousStation = m_station[i][j];
            }
        }
    }
    endStation = previousStation;

    if (startStation->getDistanceToNextStation() != nullptr && endStation->getDistanceToPreviousStation() != nullptr){
        if (startStation->getDistanceToNextStation() == endStation->getDistanceToPreviousStation()){
            endStation->getDistanceToPreviousStation()->useDefaultLineItem();
        }
    }
    if (startStation->getDistanceToPreviousStation() != nullptr && endStation->getDistanceToNextStation() != nullptr){
        if (startStation->getDistanceToPreviousStation() == endStation->getDistanceToNextStation()){
            startStation->getDistanceToPreviousStation()->useDefaultLineItem();
        }
    }

    if (ui->searchTypeBox->currentIndex() == 0){
        if (ans[end] >= INF){
            ui->notWayLabel->setText("Маршрута не существует");
            ui->lengthLabel->setText("Время в пути: 0");
        }
        else{
            ui->notWayLabel->setText("");
            ui->lengthLabel->setText("Время в пути: " + QString::number(ans[end]));
        }
    }
    else{
        if (ans[end] >= INF){
            ui->notWayLabel->setText("Маршрута не существует");
            ui->lengthLabel->setText("Количество пересадок: 0");
        }
        else{
            ui->notWayLabel->setText("");
            ui->lengthLabel->setText("Количество пересадок: " + QString::number((int)ans[end]/10000));
        }
    }
}

SubwayMap::~SubwayMap(){
    for (int i = 0; i < m_station.size(); i++){
        for (int j = 0; j < m_station[i].size(); j++){
            if (m_station[i][j]->getDistanceToNextStation()){
                delete m_station[i][j]->getDistanceToNextStation()->getLineItem();
                delete m_station[i][j]->getDistanceToNextStation();
            }
            if (m_station[i][j]->getDistanceToPreviousStation()){
                delete m_station[i][j]->getDistanceToPreviousStation()->getLineItem();
                delete m_station[i][j]->getDistanceToPreviousStation();
            }
            delete m_station[i][j];
        }
    }
    for (int i = 0; i < m_junction.size(); i++){
        delete m_junction[i];
    }
    delete m_createNewBranchDialog;
    delete m_createNewStationDialog;
    delete m_makeRingOrLineDialog;
    delete m_createJunctionDialog;
    delete scene;
    delete ui;
}
