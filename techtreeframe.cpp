#include "techtreeframe.h"
#include "ui_techtreeframe.h"

#include <QLabel>

TechTreeFrame::TechTreeFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TechTreeFrame)
{
    ui->setupUi(this);

    setStyleSheet("background-image:url(:/root/old_paper.png); background-position: top left;" );

    ui->academy1->setName("Military Academy 1");
    ui->academy2->setName("Military Academy 2");
    ui->academy3->setName("Military Academy 3");

    ui->education1->setName("Education 1");
    ui->education2->setName("Education 2");
    ui->education3->setName("Education 3");

    ui->science1->setName("Science 1");
    ui->science2->setName("Science 2");

    ui->advancedEngineering->setName("Advanced Engineering");

    ui->metallurgy1->setName("Metallurgy 1");
    ui->metallurgy2->setName("Metallurgy 2");

    ui->industry1->setName("Industry 1");
    ui->industry2->setName("Industry 2");
    ui->industry3->setName("Industry 3");

    ui->inflation1->setName("Inflation 1");
    ui->inflation2->setName("Inflation 2");

    ui->economics1->setName("Economics 1");
    ui->economics2->setName("Economics 2");
    ui->economics3->setName("Economics 3");

    ui->trade1->setName("Trade 1");
    ui->trade2->setName("Trade 2");
    ui->trade3->setName("Trade 3");

    ui->government1->setName("Government 1");
    ui->government2->setName("Government 2");
    ui->government3->setName("Government 3");

    ui->artillery1->setName("Artillery 1");
    ui->artillery2->setName("Artillery 2");
    ui->artillery3->setName("Artillery 3");

    ui->battleship1->setName("Battleship Guns 1");
    ui->battleship2->setName("Battleship Guns 2");
    ui->battleship3->setName("Battleship Guns 3");

    ui->rifles1->setName("Rifles 1");
    ui->rifles2->setName("Rifles 2");
    ui->rifles3->setName("Rifles 3");

    ui->cavalry1->setName("Cavalry 1");
    ui->cavalry2->setName("Cavalry 2");
}

TechTreeFrame::~TechTreeFrame()
{
    delete ui;
}
