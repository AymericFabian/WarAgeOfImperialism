#include "technologyframe.h"
#include "ui_technologyframe.h"

TechnologyFrame::TechnologyFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TechnologyFrame)
{
    ui->setupUi(this);
}

TechnologyFrame::~TechnologyFrame()
{
    delete ui;
}

void TechnologyFrame::setName(QString name)
{
    ui->labelName->setText(name);
}
