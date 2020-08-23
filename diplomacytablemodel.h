#ifndef DIPLOMACYTABLEMODEL_H
#define DIPLOMACYTABLEMODEL_H

#include <QAbstractTableModel>

class DiplomacyTableModel : public QAbstractTableModel
{
public:
    DiplomacyTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & /*parent*/) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);
private:
    static QList<QString> columnNames;
};

#endif // DIPLOMACYTABLEMODEL_H
