#ifndef HISTORYFRAME_H
#define HISTORYFRAME_H

#include <QFrame>

#include "historystate.h"
#include "countrieschart.h"
#include "incomechart.h"

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
    void reset();

private:
    Ui::HistoryFrame *ui;

    CountriesChart* countriesChart;
    IncomeChart* incomeChart;
};

#endif // HISTORYFRAME_H
