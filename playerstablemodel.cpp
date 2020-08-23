#include "playerstablemodel.h"
#include "world.h"
#include "player.h"

#include <QDebug>
#include <QBrush>
#include <QFont>

QList<QString> PlayersTableModel::columnNames = { "Name", "Income", "Bank", "Blockades", "Resources", "Cities", "Factories", "Railroads", "Ports", "Schools", "Forts" };

PlayersTableModel::PlayersTableModel(QObject *parent) : QAbstractTableModel(parent)
{
}

int PlayersTableModel::rowCount(const QModelIndex & /*parent*/) const
{
    return World::GetInstance()->players.size();
}

int PlayersTableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return (int)Columns::Forts + 1;
}

QVariant PlayersTableModel::headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const
{
    switch (role) {
    case Qt::DisplayRole:
        if(orientation == Qt::Orientation::Horizontal)
        {
            return columnNames.at(section);
        }
        else if(orientation == Qt::Orientation::Vertical)
        {
            return section;
        }
    }
    return QVariant();
}

QVariant PlayersTableModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    Player* player = World::GetInstance()->players.at(row);

    switch (role) {
    case Qt::DisplayRole:
        switch(col){
        case (int)Columns::Name:
            return player->name;
        case (int)Columns::Income:
            return player->income;
        case (int)Columns::Bank:
            return player->bank;
        case (int)Columns::Resources:
            return player->incomeFromResources();
        case (int)Columns::Blockades:
            return player->blockades();
        case (int)Columns::Cities:
            return QString::number(player->buildings(BuildingPrimary::City)) + " (" + QString::number(player->incomeFromBuildings(BuildingPrimary::City)) + ")";
        case (int)Columns::Factories:
            return QString::number(player->buildings(BuildingPrimary::Factory)) + " (" + QString::number(player->incomeFromBuildings(BuildingPrimary::Factory)) + ")";
        case (int)Columns::Railroads:
            return QString::number(player->buildings(BuildingPrimary::Railroad)) + " (" + QString::number(player->incomeFromBuildings(BuildingPrimary::Railroad)) + ")";
        case (int)Columns::Ports:
            return QString::number(player->buildings(BuildingPrimary::Port)) + " (" + QString::number(player->incomeFromBuildings(BuildingPrimary::Port)) + ")";
        case (int)Columns::Schools:
            return player->schools();
        case (int)Columns::Forts:
            return player->forts();
        }
    case Qt::ForegroundRole:
        if(player->color.red() + player->color.green() + player->color.blue() < 383)
            return QBrush(QColor(Qt::white));
        else
            return QBrush(QColor(Qt::black));
    case Qt::BackgroundRole:
        return QBrush(player->color);
    }
    return QVariant();
}

Qt::ItemFlags PlayersTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if (index.column() == (int)Columns::Name ||
        index.column() == (int)Columns::Bank ||
        index.column() == (int)Columns::Blockades)
        flags |= Qt::ItemIsEditable;
    return flags;
}

bool PlayersTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Player* player = World::GetInstance()->players.at(index.row());

    if (role == Qt::EditRole)
    {
        if (!checkIndex(index))
            return false;

        switch(index.column()){
        case (int)Columns::Name:
            player->name = value.toString();
            return true;
        case (int)Columns::Bank:
            player->bank = value.toInt();
            return true;
        case (int)Columns::Blockades:
            player->setBlockades(value.toInt());
            return true;
        }
        return true;
    }
    return false;
}
