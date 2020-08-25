#include "historyframe.h"
#include "ui_historyframe.h"

#include <QtCharts>

using namespace QtCharts;

HistoryFrame::HistoryFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::HistoryFrame)
{
    ui->setupUi(this);
}

HistoryFrame::~HistoryFrame()
{
    delete ui;
}
