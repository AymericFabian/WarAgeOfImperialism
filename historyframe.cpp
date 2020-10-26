#include "historyframe.h"
#include "ui_historyframe.h"
#include "world.h"

HistoryFrame::HistoryFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::HistoryFrame)
{
    ui->setupUi(this);

    countriesChart = new CountriesChart(this);
    incomeChart = new IncomeChart(this);
    incomeTotalChart = new IncomeTotalChart(this);
    buildingsChart = new BuildingsChart(this);

    ui->tabCountries->layout()->addWidget(countriesChart);
    ui->tabIncome->layout()->addWidget(incomeChart);
    ui->tabTotalIncome->layout()->addWidget(incomeTotalChart);
    ((QGridLayout*)ui->tabBuildings->layout())->addWidget(buildingsChart,1,0,1,7);

    QButtonGroup* bgroup = new QButtonGroup(this);
    bgroup->addButton(ui->buttonCity);
    bgroup->addButton(ui->buttonFactory);
    bgroup->addButton(ui->buttonRailroad);
    bgroup->addButton(ui->buttonPort);
    bgroup->addButton(ui->buttonSchool);
    bgroup->addButton(ui->buttonFort);
    bgroup->setExclusive(true);

    ui->buttonCity->toggle();

    connect(ui->buttonCity, &QPushButton::toggled, [=] (bool) {buildingsChart->setBuildingType(BuildingPrimary::City);});
    connect(ui->buttonFactory, &QPushButton::toggled, [=] (bool) {buildingsChart->setBuildingType(BuildingPrimary::Factory);});
    connect(ui->buttonPort, &QPushButton::toggled, [=] (bool) {buildingsChart->setBuildingType(BuildingPrimary::Port);});
    connect(ui->buttonRailroad, &QPushButton::toggled, [=] (bool) {buildingsChart->setBuildingType(BuildingPrimary::Railroad);});
    connect(ui->buttonSchool, &QPushButton::toggled, [=] (bool) {buildingsChart->setBuildingType(BuildingPrimary::School);});
    connect(ui->buttonFort, &QPushButton::toggled, [=] (bool) {buildingsChart->setBuildingType(BuildingPrimary::Fort);});

    reset();
}

void HistoryFrame::addState(HistoryState* hs)
{
    countriesChart->addState(hs);
    incomeChart->addState(hs);
    incomeTotalChart->addState(hs);
    buildingsChart->addState(hs);
}

void HistoryFrame::deleteState()
{
    World::GetInstance()->deleteState();
    reset();
}

void HistoryFrame::reset()
{
    countriesChart->reset();
    incomeChart->reset();
    incomeTotalChart->reset();
    buildingsChart->reset();

    for(HistoryState* hs : World::GetInstance()->history)
        addState(hs);
}

HistoryFrame::~HistoryFrame()
{
    delete ui;
}
