#ifndef INCOMETOTALCHART_H
#define INCOMETOTALCHART_H

#include <QtCharts>

#include "historystate.h"

class IncomeTotalChart : public QChartView
{
public:
    IncomeTotalChart(QWidget *parent = nullptr);

    void addState(HistoryState *hs);
    void reset();

private:
    QChart *incomeChart;
    QBarSeries *barSeries;

    QValueAxis* axisY;
    QBarCategoryAxis *axisX;
};

#endif // INCOMETOTALCHART_H
