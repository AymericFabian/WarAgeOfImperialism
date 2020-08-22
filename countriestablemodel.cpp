#include "countriestablemodel.h"
#include "world.h"
#include "player.h"

#include <QDebug>
#include <QBrush>
#include <QFont>

CountriesTableModel::CountriesTableModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int CountriesTableModel::rowCount(const QModelIndex & /*parent*/) const
{
   return World::GetInstance()->countries.size();
}

int CountriesTableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 5;
}

QVariant CountriesTableModel::headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const
{
    switch (role) {
    case Qt::DisplayRole:
        if(orientation == Qt::Orientation::Horizontal)
        {
            switch(section){
            case (int)Columns::Continent:
                return "Continent";
            case (int)Columns::Player:
                return "Player";
            case (int)Columns::Building:
                return "Building";
            case (int)Columns::School:
                return "School";
            case (int)Columns::Fort:
                return "Fort";
            case (int)Columns::Resource:
                return "Resource";
            }
        }
        else if(orientation == Qt::Orientation::Vertical)
        {
            return World::GetInstance()->countries.at(section).getName();
        }
        break;
    }
    return QVariant();
}

QVariant CountriesTableModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    switch (role) {
    case Qt::DisplayRole:
        switch(col){
        case (int)Columns::Continent:
            return Country::getContinentName(World::GetInstance()->countries.at(row).getContinent());
        case (int)Columns::Player:
            return World::GetInstance()->countries.at(row).getPlayer()->name;
        case (int)Columns::Building:
            //return World::GetInstance()->countries.at(row).getBuildingPrim().;
            return "";
        case (int)Columns::School:
            return "";
        case (int)Columns::Fort:
            return "";
        case (int)Columns::Resource:
            return World::GetInstance()->countries.at(row).getResource();
        }
    case Qt::FontRole:
//        if (row == 0 && col == 0) {
//            QFont boldFont;
//            boldFont.setBold(true);
//            return boldFont;
//        }
        break;
    case Qt::BackgroundRole:
        if (col == (int)Columns::Player)
            return QBrush(World::GetInstance()->countries.at(row).getPlayer()->color);
        else
            return QBrush(World::GetInstance()->countries.at(row).getColor());
        break;
    case Qt::TextAlignmentRole:
//        if (row == 1 && col == 1)
//            return Qt::AlignRight + Qt::AlignVCenter;
        break;
    case Qt::CheckStateRole:
//        if (row == 1 && col == 0)
//            return Qt::Checked;
        break;
    }
    return QVariant();
}
