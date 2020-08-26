#include "playersframe.h"
#include "ui_playersframe.h"

PlayersFrame::PlayersFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PlayersFrame)
{
    ui->setupUi(this);

    playersTableModel = new PlayersTableModel(this);
    ui->tableView->setModel(playersTableModel);
}

PlayersFrame::~PlayersFrame()
{
    delete ui;
}
