#include "buildingschart.h"
#include "world.h"

BuildingsChart::BuildingsChart(QWidget *parent) : QChartView(parent)
{
    buildingsChart = new QChart();
    buildingsChart->setTitle("Buildings in empire");

    axisY = new QValueAxis();
    axisY->setTickCount(10);
    axisY->setLabelFormat("%i");
    axisY->setRange(0, 20);
    buildingsChart->addAxis(axisY, Qt::AlignLeft);

    axisX = new QBarCategoryAxis();
    barSeries = new QStackedBarSeries();
    buildingsChart->addSeries(barSeries);
    buildingsChart->addAxis(axisX, Qt::AlignBottom);

    setChart(buildingsChart);
    setRenderHint(QPainter::Antialiasing);
    chart()->legend()->hide();
}

void BuildingsChart::setBuildingType(BuildingPrimary type)
{
    currentBuildingType = type;
    reset();
    for(HistoryState* hs : World::GetInstance()->history)
        addState(hs);
}

void BuildingsChart::addState(HistoryState* hs)
{
    for(int i=0; i<hs->playersState.size(); i++)
    {
        HistoryState::PlayerState* ps = hs->playersState[i];
        barSeries->barSets()[i]->append(ps->getBuildingsOfType(currentBuildingType));
    }
    axisX->append(hs->date.toString("MMM yyyy"));
}

void BuildingsChart::resizeEvent(QResizeEvent* event)
{
    QChartView::resizeEvent(event);
    //axisX->setTickCount(qMin((int)event->size().width() / 80, World::GetInstance()->history.count()));
}

void BuildingsChart::reset()
{
    barSeries->clear();
    for(int i=0; i<World::GetInstance()->players.size(); i++)
        barSeries->append(new QBarSet(World::GetInstance()->players[i]->name));

    for(int i=0; i<barSeries->barSets().size();i++)
    {
        QPen pen(World::GetInstance()->players[i]->color);
        pen.setWidth(1);
        barSeries->barSets()[i]->setPen(pen);

        QBrush brush(barSeries->barSets()[i]->brush());
        QColor col = World::GetInstance()->players[i]->color;
        col.setAlpha(128);
        brush.setColor(col);
        barSeries->barSets()[i]->setBrush(brush);
    }

    for(QAbstractSeries* qas : buildingsChart->series())
    {
        qas->attachAxis(axisX);
        qas->attachAxis(axisY);
    }
}
