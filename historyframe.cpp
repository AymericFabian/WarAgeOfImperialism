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

    ui->tabCountries->layout()->addWidget(countriesChart);
    ui->tabIncome->layout()->addWidget(incomeChart);

    reset();
}

void HistoryFrame::addState(HistoryState* hs)
{
    countriesChart->addState(hs);
    incomeChart->addState(hs);
}

void HistoryFrame::reset()
{
    countriesChart->reset();
    incomeChart->reset();

    for(HistoryState* hs : World::GetInstance()->history)
        addState(hs);
}

HistoryFrame::~HistoryFrame()
{
    delete ui;
}
