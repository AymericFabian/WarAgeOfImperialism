#ifndef HISTORYFRAME_H
#define HISTORYFRAME_H

#include <QFrame>

#include "historystate.h"
#include "countrieschart.h"
#include "incomechart.h"
#include "incometotalchart.h"
#include "buildingschart.h"

namespace Ui {
class HistoryFrame;
}

class HistoryFrame : public QFrame
{
    Q_OBJECT

public:
    explicit HistoryFrame(QWidget *parent = nullptr);
    ~HistoryFrame();

    void addState(HistoryState *hs);
    void deleteState();
    void reset();

private:
    Ui::HistoryFrame *ui;

    CountriesChart* countriesChart;
    IncomeChart* incomeChart;
    IncomeTotalChart* incomeTotalChart;
    BuildingsChart* buildingsChart;
};

#endif // HISTORYFRAME_H
