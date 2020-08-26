#ifndef INCOMECHART_H
#define INCOMECHART_H

#include <QtCharts>

#include "historystate.h"

class IncomeChart : public QChartView
{
public:
    IncomeChart(QWidget *parent = nullptr);

    void addState(HistoryState *hs);
    void reset();

private:
    QChart *incomeChart;

    QValueAxis* axisY;
    QDateTimeAxis *axisX;
};

#endif // INCOMECHART_H
