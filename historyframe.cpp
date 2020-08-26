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

    ui->tabCountries->layout()->addWidget(countriesChart);
    ui->tabIncome->layout()->addWidget(incomeChart);
    ui->tabTotalIncome->layout()->addWidget(incomeTotalChart);

    reset();
}

void HistoryFrame::addState(HistoryState* hs)
{
    countriesChart->addState(hs);
    incomeChart->addState(hs);
    incomeTotalChart->addState(hs);
}

void HistoryFrame::reset()
{
    countriesChart->reset();
    incomeChart->reset();
    incomeTotalChart->reset();

    for(HistoryState* hs : World::GetInstance()->history)
        addState(hs);
}

HistoryFrame::~HistoryFrame()
{
    delete ui;
}
