#include "countriesframe.h"
#include "ui_countriesframe.h"

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
}
