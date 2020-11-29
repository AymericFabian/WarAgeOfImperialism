#ifndef COUNTRIESCHART_H
#define COUNTRIESCHART_H

#include <QtCharts>

#include "historystate.h"

class CountriesChart : public QChartView
{
public:
    CountriesChart(QWidget *parent = nullptr);

    void addState(HistoryState *hs);
    void reset();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    QChart *countriesChart;

    QValueAxis* axisY;
    QDateTimeAxis *axisX;
};

#endif // COUNTRIESCHART_H
