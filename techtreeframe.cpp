#include "techtreeframe.h"
#include "ui_techtreeframe.h"
#include "world.h"

#include <QLabel>

TechTreeFrame::TechTreeFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TechTreeFrame)
{
    ui->setupUi(this);

    setStyleSheet("background-image:url(:/root/old_paper.png); background-position: top left;" );

    ui->academy1->init(Player::Technology::MilitaryAcademy, 1);
    ui->academy2->init(Player::Technology::MilitaryAcademy, 2);
    ui->academy3->init(Player::Technology::MilitaryAcademy, 3);

    ui->education1->init(Player::Technology::Education, 1);
    ui->education2->init(Player::Technology::Education, 2);
    ui->education3->init(Player::Technology::Education, 3);

    ui->science1->init(Player::Technology::Science, 1);
    ui->science2->init(Player::Technology::Science, 2);

    ui->advancedEngineering->init(Player::Technology::AdvancedEngineering, 1);

    ui->metallurgy1->init(Player::Technology::Metallurgy, 1);
    ui->metallurgy2->init(Player::Technology::Metallurgy, 2);

    ui->industry1->init(Player::Technology::Industry, 1);
    ui->industry2->init(Player::Technology::Industry, 2);
    ui->industry3->init(Player::Technology::Industry, 3);

    ui->inflation1->init(Player::Technology::Inflation, 1);
    ui->inflation2->init(Player::Technology::Inflation, 2);

    ui->economics1->init(Player::Technology::Economics, 1);
    ui->economics2->init(Player::Technology::Economics, 2);
    ui->economics3->init(Player::Technology::Economics, 3);

    ui->trade1->init(Player::Technology::Trade, 1);
    ui->trade2->init(Player::Technology::Trade, 2);
    ui->trade3->init(Player::Technology::Trade, 3);

    ui->government1->init(Player::Technology::Government, 1);
    ui->government2->init(Player::Technology::Government, 2);
    ui->government3->init(Player::Technology::Government, 3);

    ui->artillery1->init(Player::Technology::Artillery, 1);
    ui->artillery2->init(Player::Technology::Artillery, 2);
    ui->artillery3->init(Player::Technology::Artillery, 3);

    ui->battleship1->init(Player::Technology::BattleshipGuns, 1);
    ui->battleship2->init(Player::Technology::BattleshipGuns, 2);
    ui->battleship3->init(Player::Technology::BattleshipGuns, 3);

    ui->rifles1->init(Player::Technology::Rifles, 1);
    ui->rifles2->init(Player::Technology::Rifles, 2);
    ui->rifles3->init(Player::Technology::Rifles, 3);

    ui->cavalry1->init(Player::Technology::Cavalry, 1);
    ui->cavalry2->init(Player::Technology::Cavalry, 2);

    for(TechnologyFrame* techFrame : findChildren<TechnologyFrame*>())
        connect(techFrame, SIGNAL(researched(int, Player::Technology, int, bool)), this, SLOT(onResearch(int,Player::Technology,int,bool)));
}

void TechTreeFrame::reset()
{
    for(TechnologyFrame* techFrame : findChildren<TechnologyFrame*>())
        techFrame->reset();
}

void TechTreeFrame::onResearch(int player, Player::Technology techno, int level, bool researched)
{
    World::GetInstance()->ResearchTech(player, techno, level, researched);

    for(TechnologyFrame* techFrame : findChildren<TechnologyFrame*>())
        techFrame->updateStatus(player, techno, level, researched);
}

TechTreeFrame::~TechTreeFrame()
{
    delete ui;
}
