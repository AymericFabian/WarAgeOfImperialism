#include "countriesframe.h"
#include "ui_countriesframe.h"
#include "buildingdelegate.h"
#include "playerdelegate.h"

#include <QCheckBox>

CountriesFrame::CountriesFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CountriesFrame)
{
    ui->setupUi(this);
    init();
}

CountriesFrame::~CountriesFrame()
{
    delete ui;
}

void CountriesFrame::init()
{
    countriesTableModel = new CountriesTableModel(this);
    ui->tableView->setModel(countriesTableModel);

    ui->tableView->setItemDelegateForColumn((int)CountriesTableModel::Columns::Player, new PlayerDelegate(ui->tableView));
    ui->tableView->setItemDelegateForColumn((int)CountriesTableModel::Columns::Building, new BuildingDelegate(ui->tableView));
}
