#include "techtreeframe.h"
#include "ui_techtreeframe.h"
#include "world.h"

#include <QLabel>
#include <QPainter>

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

    arrows << new Arrow(ui->education1,             ui->science1,               Arrow::Position::TopRightMid,   Arrow::Position::Left);
    arrows << new Arrow(ui->education2,             ui->science2,               Arrow::Position::TopRightMid,   Arrow::Position::Left);
    arrows << new Arrow(ui->education3,             ui->advancedEngineering,    Arrow::Position::TopRightMid,   Arrow::Position::BotLeftMid);

    arrows << new Arrow(ui->science1,               ui->industry2,              Arrow::Position::RightTopMid,   Arrow::Position::LeftBotMid);
    arrows << new Arrow(ui->science1,               ui->metallurgy1,            Arrow::Position::TopRightMid,   Arrow::Position::BotLeftMid);

    arrows << new Arrow(ui->science2,               ui->education3,             Arrow::Position::TopLeftMid,    Arrow::Position::Right);
    arrows << new Arrow(ui->science2,               ui->metallurgy2,            Arrow::Position::TopRightMid,   Arrow::Position::Bot);
    arrows << new Arrow(ui->science2,               ui->inflation2,             Arrow::Position::TopRightMid,   Arrow::Position::Left);

    arrows << new Arrow(ui->advancedEngineering,    ui->academy2,               Arrow::Position::TopLeftMid,    Arrow::Position::BotRightMid);
    arrows << new Arrow(ui->metallurgy1,            ui->advancedEngineering,    Arrow::Position::TopLeftMid,    Arrow::Position::BotRightMid);
    arrows << new Arrow(ui->metallurgy2,            ui->academy3,               Arrow::Position::TopLeft,       Arrow::Position::BotRightMid);

    arrows << new Arrow(ui->rifles1,            ui->cavalry1,               Arrow::Position::Right,         Arrow::Position::BotLeftMid);
    arrows << new Arrow(ui->rifles2,            ui->cavalry2,               Arrow::Position::TopRight,      Arrow::Position::BotLeftMid);
    arrows << new Arrow(ui->artillery1,         ui->battleship1,            Arrow::Position::Right,         Arrow::Position::BotLeftMid);
    arrows << new Arrow(ui->artillery2,         ui->battleship2,            Arrow::Position::TopRightMid,   Arrow::Position::BotLeftMid);
    arrows << new Arrow(ui->artillery3,         ui->battleship3,            Arrow::Position::TopRightMid,   Arrow::Position::BotLeftMid);

    arrows << new Arrow(ui->government1,        ui->trade1,         Arrow::Position::Left,          Arrow::Position::BotRightMid);
    arrows << new Arrow(ui->government2,        ui->trade2,         Arrow::Position::TopLeftMid,    Arrow::Position::BotRightMid);
    arrows << new Arrow(ui->government3,        ui->trade3,         Arrow::Position::Left,          Arrow::Position::BotRightMid);

    arrows << new Arrow(ui->economics2,         ui->government2,    Arrow::Position::TopRightMid,  Arrow::Position::LeftBotMid);
    arrows << new Arrow(ui->economics3,         ui->government3,    Arrow::Position::TopRightMid,  Arrow::Position::LeftBotMid);

    arrows << new Arrow(ui->industry1,      ui->science1,       Arrow::Position::LeftTopMid,    Arrow::Position::RightBotMid);
    arrows << new Arrow(ui->industry1,      ui->artillery1,     Arrow::Position::Right,         Arrow::Position::LeftBotMid);
    arrows << new Arrow(ui->industry1,      ui->rifles1,        Arrow::Position::RightBotMid,   Arrow::Position::BotLeft);
    arrows << new Arrow(ui->industry1,      ui->economics1,     Arrow::Position::TopRightMid,   Arrow::Position::Left);

    arrows << new Arrow(ui->industry2,      ui->metallurgy1,    Arrow::Position::LeftTopMid,    Arrow::Position::BotRightMid);
    arrows << new Arrow(ui->industry2,      ui->artillery2,     Arrow::Position::Right,         Arrow::Position::LeftBotMid);
    arrows << new Arrow(ui->industry2,      ui->rifles2,        Arrow::Position::RightBotMid,   Arrow::Position::BotLeft);
    arrows << new Arrow(ui->industry2,      ui->economics2,     Arrow::Position::TopRightMid,   Arrow::Position::Left);

    arrows << new Arrow(ui->inflation1,     ui->government1,    Arrow::Position::Right,  Arrow::Position::LeftBotMid);
    arrows << new Arrow(ui->inflation2,     ui->trade2,         Arrow::Position::Right,  Arrow::Position::LeftBotMid);

    arrows << new Arrow(ui->industry3,      ui->metallurgy2,    Arrow::Position::LeftTopMid,    Arrow::Position::BotRightMid);
    arrows << new Arrow(ui->industry3,      ui->artillery3,     Arrow::Position::Right,         Arrow::Position::LeftBotMid);
    arrows << new Arrow(ui->industry3,      ui->rifles3,        Arrow::Position::RightBotMid,   Arrow::Position::LeftBotMid);
    arrows << new Arrow(ui->industry3,      ui->economics3,     Arrow::Position::TopRightMid,   Arrow::Position::Left);
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

void TechTreeFrame::paintEvent(QPaintEvent* /*event*/)
{
    QPainter painter(this);
    for(Arrow* arrow : arrows)
        arrow->paint(&painter, this);
}

TechTreeFrame::~TechTreeFrame()
{
    delete ui;
}
