#include "incomechart.h"
#include "world.h"

IncomeChart::IncomeChart(QWidget *parent) : QChartView(parent)
{
    incomeChart = new QChart();
    incomeChart->setTitle("Production Points");

    axisY = new QValueAxis();
    axisY->setTickCount(10);
    axisY->setLabelFormat("%i");
    axisY->setRange(0, 100);
    incomeChart->addAxis(axisY, Qt::AlignLeft);

    axisX = new QDateTimeAxis;
    axisX->setTickCount(2);
    axisX->setFormat("MMM yyyy");
    incomeChart->addAxis(axisX, Qt::AlignBottom);

    setChart(incomeChart);
    setRenderHint(QPainter::Antialiasing);
    chart()->legend()->hide();
}

void IncomeChart::addState(HistoryState* hs)
{
    for(int i=1; i<hs->playersState.size(); i++)
    {
        HistoryState::PlayerState* ps = hs->playersState[i];

        QLineSeries* line = (QLineSeries*)incomeChart->series()[i-1];

        line->append(hs->date.toMSecsSinceEpoch(), ps->getIncome());

        if(ps->getIncome() > axisY->max())
            axisY->setMax(ps->getIncome());
    }

    axisX->setTickCount(qMin((int)incomeChart->size().width() / 200, World::GetInstance()->history.count()));
    axisX->setRange(World::GetInstance()->history[0]->date, hs->date);
}

void IncomeChart::resizeEvent(QResizeEvent* event)
{
    QChartView::resizeEvent(event);
    axisX->setTickCount(qMin((int)event->size().width() / 80, World::GetInstance()->history.count()));
}

void IncomeChart::reset()
{
    incomeChart->removeAllSeries();
    for(int i=1; i<World::GetInstance()->players.size(); i++)
        incomeChart->addSeries(new QLineSeries());

    for(int i=0; i<incomeChart->series().size();i++)
    {
        QPen pen(World::GetInstance()->players[i+1]->color);
        pen.setWidth(2);
        ((QLineSeries*)incomeChart->series()[i])->setPen(pen);
    }

    for(QAbstractSeries* qas : incomeChart->series())
    {
        qas->attachAxis(axisX);
        qas->attachAxis(axisY);
    }
}
