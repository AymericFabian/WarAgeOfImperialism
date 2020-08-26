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

    for(TechPlayerButton* but : findChildren<TechPlayerButton*>())
        connect(but, SIGNAL(toggled(bool)), this, SLOT(technoToggled(bool)));
}

void TechnologyFrame::reset()
{
    blockSignals(true);
    for(TechPlayerButton* but : findChildren<TechPlayerButton*>())
    {
        if(World::GetInstance()->players.at((int)but->color + 1)->technologies[techno] >= level)
            but->setChecked(true);
        if(World::GetInstance()->players.at((int)but->color + 1)->technologies[techno] > level)
            but->setEnabled(false);
    }
    blockSignals(false);
}

void TechnologyFrame::technoToggled(bool)
{
    TechPlayerButton* but = static_cast<TechPlayerButton*>(sender());
    emit researched((int)but->color + 1, techno, level, but->isChecked());
}

void TechnologyFrame::updateStatus(int player, Player::Technology techno, int level, bool researched)
{
    if(this->techno == techno && level == this->level + 1)
        for(TechPlayerButton* but : findChildren<TechPlayerButton*>())
            if((int)but->color == player - 1)
                but->setEnabled(!researched);
}

TechnologyFrame::~TechnologyFrame()
{
    delete ui;
}
