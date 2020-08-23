#include "diplomacyframe.h"
#include "ui_diplomacyframe.h"

DiplomacyFrame::DiplomacyFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DiplomacyFrame)
{
    ui->setupUi(this);
    init();
}

DiplomacyFrame::~DiplomacyFrame()
{
    delete ui;
}

void DiplomacyFrame::init()
{
    diploTableModel = new DiplomacyTableModel(this);
    ui->tableView->setModel(diploTableModel);
}
