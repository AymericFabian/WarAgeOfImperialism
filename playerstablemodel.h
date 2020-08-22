#ifndef PLAYERSTABLEMODEL_H
#define PLAYERSTABLEMODEL_H

#include <QAbstractTableModel>

class PlayersTableModel : public QAbstractTableModel
{
public:
    enum class Columns { Name, Income, Bank, Resources, Blockades };

    explicit PlayersTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & /*parent*/) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);
private:
    static QList<QString> columnNames;
};

#endif // PLAYERSTABLEMODEL_H
