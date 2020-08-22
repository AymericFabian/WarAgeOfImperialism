#include "playerstablemodel.h"
#include "world.h"

#include <QDebug>
#include <QBrush>
#include <QFont>

PlayersTableModel::PlayersTableModel(QObject *parent) : QAbstractTableModel(parent)
{
}

int PlayersTableModel::rowCount(const QModelIndex & /*parent*/) const
{
   return 6;
}

int PlayersTableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 5;
}

QVariant PlayersTableModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    switch (role) {
    case Qt::DisplayRole:
        return World::GetInstance()->countries.at(row).getName();
    case Qt::FontRole:
        if (row == 0 && col == 0) { //change font only for cell(0,0)
            QFont boldFont;
            boldFont.setBold(true);
            return boldFont;
        }
        break;
    case Qt::BackgroundRole:
        if (row == 1 && col == 2)  //change background only for cell(1,2)
            return QBrush(Qt::red);
        break;
    case Qt::TextAlignmentRole:
        if (row == 1 && col == 1) //change text alignment only for cell(1,1)
            return Qt::AlignRight + Qt::AlignVCenter;
        break;
    case Qt::CheckStateRole:
        if (row == 1 && col == 0) //add a checkbox to cell(1,0)
            return Qt::Checked;
        break;
    }
    return QVariant();
}
