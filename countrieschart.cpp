#include "countrieschart.h"
#include "world.h"

CountriesChart::CountriesChart(QWidget *parent) : QChartView(parent)
{
    countriesChart = new QChart();
    countriesChart->setTitle("Countries in empire");

    axisY = new QValueAxis();
    axisY->setTickCount(10);
    axisY->setLabelFormat("%i");
    axisY->setRange(0, World::GetInstance()->countries.size());
    countriesChart->addAxis(axisY, Qt::AlignLeft);

    axisX = new QDateTimeAxis;
    axisX->setTickCount(2);
    axisX->setFormat("MMM yyyy");
    countriesChart->addAxis(axisX, Qt::AlignBottom);

    setChart(countriesChart);
    setRenderHint(QPainter::Antialiasing);
    chart()->legend()->hide();
}


void CountriesChart::addState(HistoryState* hs)
{
    int currentCountryCount = 0;
    for(int i=0; i<hs->playersState.size(); i++)
    {
        HistoryState::PlayerState* ps = hs->playersState[i];

        QAreaSeries* area = (QAreaSeries*)countriesChart->series()[i];

        area->upperSeries()->append(hs->date.toMSecsSinceEpoch(), ps->getCountries() + currentCountryCount);
        area->lowerSeries()->append(hs->date.toMSecsSinceEpoch(), currentCountryCount);

        currentCountryCount += ps->getCountries();
    }
    axisX->setTickCount(World::GetInstance()->history.count());
    axisX->setRange(World::GetInstance()->history[0]->date, hs->date);
}

void CountriesChart::reset()
{
    countriesChart->removeAllSeries();
    for(int i=0; i<World::GetInstance()->players.size(); i++)
        countriesChart->addSeries(new QAreaSeries(new QLineSeries(), new QLineSeries()));

    for(int i=0; i<countriesChart->series().size();i++)
    {
        QPen pen(World::GetInstance()->players[i]->color);
        pen.setWidth(1);
        ((QAreaSeries*)countriesChart->series()[i])->setPen(pen);

        QBrush brush(((QAreaSeries*)countriesChart->series()[i])->brush());
        QColor col = World::GetInstance()->players[i]->color;
        col.setAlpha(128);
        brush.setColor(col);
        ((QAreaSeries*)countriesChart->series()[i])->setBrush(brush);
    }

    for(QAbstractSeries* qas : countriesChart->series())
    {
        qas->attachAxis(axisX);
        qas->attachAxis(axisY);
    }
}
