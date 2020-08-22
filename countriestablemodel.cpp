#include "countriestablemodel.h"
#include "world.h"
#include "player.h"

#include <QDebug>
#include <QBrush>
#include <QFont>

QList<QString> CountriesTableModel::columnNames = { "Continent", "Player", "Building", "School", "Fort", "Resources" };

CountriesTableModel::CountriesTableModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int CountriesTableModel::rowCount(const QModelIndex & /*parent*/) const
{
   return World::GetInstance()->countries.size();
}

int CountriesTableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return (int)Columns::Resource + 1;
}

QVariant CountriesTableModel::headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const
{
    switch (role) {
    case Qt::DisplayRole:
        if(orientation == Qt::Orientation::Horizontal)
        {
            return columnNames.at(section);
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

    Country& country = World::GetInstance()->countries[row];

    switch (role) {
    case Qt::DisplayRole:
        switch(col){
        case (int)Columns::Continent:
            return Country::getContinentName(country.getContinent());
        case (int)Columns::Player:
            return country.getPlayer()->name;
        case (int)Columns::Building:
            return Country::getBuildingName(country.getBuildingPrim());
        case (int)Columns::Resource:
            return country.getResource();
        }
    case Qt::ForegroundRole:
        if (col == (int)Columns::Player)
            if(country.getPlayer()->color.red() + country.getPlayer()->color.green() + country.getPlayer()->color.blue() < 383)
                return QBrush(QColor(Qt::white));
            else
                return QBrush(QColor(Qt::black));
        else
        {
            if(country.getColor().red() + country.getColor().green() + country.getColor().blue() < 345)
                return QBrush(QColor(Qt::white));
            else
                return QBrush(QColor(Qt::black));
        }
    case Qt::BackgroundRole:
        if (col == (int)Columns::Player)
            return QBrush(country.getPlayer()->color);
        else
            return QBrush(country.getColor());
        break;
    case Qt::CheckStateRole:
        if (col == (int)Columns::Fort)
            return country.hasFort() ? Qt::CheckState::Checked : Qt::CheckState::Unchecked;
        if (col == (int)Columns::School)
            return country.hasSchool() ? Qt::CheckState::Checked : Qt::CheckState::Unchecked;
        break;
    }
    return QVariant();
}

Qt::ItemFlags CountriesTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if (index.column() == (int)Columns::Player
            || index.column() == (int)Columns::Resource
            || index.column() == (int)Columns::Building)
        flags |= Qt::ItemIsEditable;
    if (index.column() == (int)Columns::School
            || index.column() == (int)Columns::Fort)
        flags |= Qt::ItemIsUserCheckable;
    return flags;
}

bool CountriesTableModel::setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)
{
    Country& country = World::GetInstance()->countries[index.row()];

    if (role == Qt::EditRole)
    {
        switch(index.column()){
        case (int)Columns::Player:
            country.setPlayer(World::GetInstance()->getPlayerByName(value.toString()));
            return true;
        case (int)Columns::Building:
            country.setBuilding(Country::getBuildingType(value.toString()));
            return true;
        case (int)Columns::Resource:
            country.setResource(value.toInt());
            return true;
        }
    }
    else if (role == Qt::CheckStateRole)
    {
        switch(index.column()){
        case (int)Columns::Fort:
            country.setFort(!country.hasFort());
            return true;
        case (int)Columns::School:
            country.setSchool(!country.hasSchool());
            return true;
        }
    }
    return false;
}
