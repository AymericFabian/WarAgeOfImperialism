#include "diplomacytablemodel.h"
#include "world.h"
#include "player.h"
#include <QBrush>

DiplomacyTableModel::DiplomacyTableModel(QObject *parent) : QAbstractTableModel(parent)
{
}

int DiplomacyTableModel::rowCount(const QModelIndex & /*parent*/) const
{
    return World::GetInstance()->players.size() - 1;
}

int DiplomacyTableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return World::GetInstance()->players.size() - 1;
}

QVariant DiplomacyTableModel::headerData(int section, Qt::Orientation /*orientation*/, int role = Qt::DisplayRole) const
{
    switch (role) {
    case Qt::DisplayRole:
        return World::GetInstance()->players.at(section+1)->name;
    }
    return QVariant();
}

QVariant DiplomacyTableModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    Player* player = World::GetInstance()->players.at(row+1);

    switch (role) {
    case Qt::DisplayRole:
        if(row == col)
            return QVariant();
        if(player->enemy[col+1])
            return "war";
        else
            return "peace";
    case Qt::ForegroundRole:
        return QBrush(QColor(Qt::black));
    case Qt::BackgroundRole:
        if(row == col)
            return QBrush(QColor(Qt::gray));
        else if(player->enemy[col+1])
            return QBrush(QColor(Qt::red));
        else
            return QBrush(QColor(Qt::green));
    case Qt::CheckStateRole:
        if(row != col)
            return player->enemy[col+1] ? Qt::CheckState::Checked : Qt::CheckState::Unchecked;
        break;
    }
    return QVariant();
}

Qt::ItemFlags DiplomacyTableModel::flags(const QModelIndex &index) const
{
    int row = index.row();
    int col = index.column();

    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if(row != col)
        flags |= Qt::ItemIsUserCheckable;
    return flags;
}

bool DiplomacyTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Player* p1 = World::GetInstance()->players.at(index.row()+1);
    Player* p2 = World::GetInstance()->players.at(index.column()+1);

    if (role == Qt::CheckStateRole)
    {
        if (!checkIndex(index))
            return false;

        p1->enemy[index.column()+1] = value.toBool();
        p2->enemy[index.row()+1] = value.toBool();

        emit dataChanged(QAbstractTableModel::index(0,0), QAbstractTableModel::index(5,5), {role});

        return true;
    }
    return false;
}
