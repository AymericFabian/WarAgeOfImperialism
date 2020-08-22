#ifndef PLAYERSTABLEMODEL_H
#define PLAYERSTABLEMODEL_H

#include <QAbstractTableModel>

class PlayersTableModel : public QAbstractTableModel
{
public:
    explicit PlayersTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & /*parent*/) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // PLAYERSTABLEMODEL_H
