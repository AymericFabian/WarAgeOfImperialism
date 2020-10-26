#include "incometotalchart.h"
#include "world.h"

IncomeTotalChart::IncomeTotalChart(QWidget *parent) : QChartView(parent)
{
    incomeChart = new QChart();
    incomeChart->setTitle("Total Production Points earned");

    axisY = new QValueAxis();
    axisY->setTickCount(10);
    axisY->setLabelFormat("%i");
    axisY->setRange(0, 100);
    incomeChart->addAxis(axisY, Qt::AlignLeft);

    axisX = new QBarCategoryAxis();
    incomeChart->addAxis(axisX, Qt::AlignBottom);

    setChart(incomeChart);
    setRenderHint(QPainter::Antialiasing);
    chart()->legend()->hide();
}

void IncomeTotalChart::addState(HistoryState* hs)
{
    for(int i=1; i<hs->playersState.size(); i++)
    {
        HistoryState::PlayerState* ps = hs->playersState[i];

        int currentTotal = 0;
        if(barSeries->barSets()[i-1]->count() > 0)
            currentTotal = barSeries->barSets()[i-1]->at(barSeries->barSets()[i-1]->count() - 1);
        barSeries->barSets()[i-1]->append(currentTotal + ps->getIncome());

        if(currentTotal + ps->getIncome() > axisY->max())
            axisY->setMax(currentTotal + ps->getIncome());
    }

    axisX->append(hs->date.toString("MMM"));
}

void IncomeTotalChart::reset()
{
    incomeChart->removeAllSeries();
    axisX->clear();

    barSeries = new QBarSeries();
    incomeChart->addSeries(barSeries);
    for(int i=1; i<World::GetInstance()->players.size(); i++)
        barSeries->append(new QBarSet(World::GetInstance()->players[i]->name));

    for(int i=0; i<barSeries->count();i++)
    {
        QBrush brush(World::GetInstance()->players[i+1]->color);
        barSeries->barSets()[i]->setBrush(brush);
    }

    barSeries->attachAxis(axisX);
    barSeries->attachAxis(axisY);
}
