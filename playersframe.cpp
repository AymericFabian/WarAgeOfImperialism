#include "playersframe.h"
#include "ui_playersframe.h"

PlayersFrame::PlayersFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PlayersFrame)
{
    ui->setupUi(this);
    init();
}

PlayersFrame::~PlayersFrame()
{
    delete ui;
}

void PlayersFrame::init()
{
    playersTableModel = new PlayersTableModel(this);
    ui->tableView->setModel(playersTableModel);
}
