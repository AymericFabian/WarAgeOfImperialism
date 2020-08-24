#include "technologyframe.h"
#include "ui_technologyframe.h"
#include "world.h"

TechnologyFrame::TechnologyFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TechnologyFrame)
{
    ui->setupUi(this);
}

void TechnologyFrame::init(Player::Technology techno, int level)
{
    this->techno = techno;
    this->level = level;
    ui->labelName->setText(Player::getTechnoName(techno) + QString::number(level));

    ui->toolButtonRed->init(TechPlayerButton::Color::Red);
    ui->toolButtonGreen->init(TechPlayerButton::Color::Green);
    ui->toolButtonBlue->init(TechPlayerButton::Color::Blue);
    ui->toolButtonYellow->init(TechPlayerButton::Color::Yellow);
    ui->toolButtonPurple->init(TechPlayerButton::Color::Purple);
    ui->toolButtonGray->init(TechPlayerButton::Color::Gray);

    if(World::GetInstance()->players.at(1)->technologies[techno] >= level)
        ui->toolButtonRed->setChecked(true);
    if(World::GetInstance()->players.at(2)->technologies[techno] >= level)
        ui->toolButtonGreen->setChecked(true);
    if(World::GetInstance()->players.at(3)->technologies[techno] >= level)
        ui->toolButtonBlue->setChecked(true);
    if(World::GetInstance()->players.at(4)->technologies[techno] >= level)
        ui->toolButtonYellow->setChecked(true);
    if(World::GetInstance()->players.at(5)->technologies[techno] >= level)
        ui->toolButtonPurple->setChecked(true);
    if(World::GetInstance()->players.at(6)->technologies[techno] >= level)
        ui->toolButtonGray->setChecked(true);

    for(TechPlayerButton* but : findChildren<TechPlayerButton*>())
        connect(but,      SIGNAL(toggled(bool)), this, SLOT(technoToggled(bool)));
}

void TechnologyFrame::technoToggled(bool)
{
    TechPlayerButton* but = static_cast<TechPlayerButton*>(sender());
    emit researched((int)but->color + 1, techno, level, but->isChecked());
}

TechnologyFrame::~TechnologyFrame()
{
    delete ui;
}
