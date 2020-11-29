#ifndef BUILDINGSCHART_H
#define BUILDINGSCHART_H

#include <QtCharts>

#include "historystate.h"

class BuildingsChart : public QChartView
{
public:
    BuildingsChart(QWidget *parent = nullptr);

    void addState(HistoryState *hs);
    void reset();

    void setBuildingType(BuildingPrimary type);
    void setBuildingTypeSchool();
    void setBuildingTypeFort();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    QChart *buildingsChart;
    QStackedBarSeries* barSeries;

    QValueAxis* axisY;
    QBarCategoryAxis* axisX;

    BuildingPrimary currentBuildingType;
};

#endif // BUILDINGSCHART_H
