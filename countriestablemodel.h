#ifndef COUNTRIESTABLEMODEL_H
#define COUNTRIESTABLEMODEL_H

#include <QAbstractTableModel>

class CountriesTableModel : public QAbstractTableModel
{
    enum class Columns { Continent, Player, Building, School, Fort, Resource };

public:
    explicit CountriesTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & /*parent*/) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // COUNTRIESTABLEMODEL_H
