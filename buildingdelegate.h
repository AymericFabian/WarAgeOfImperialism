#ifndef BUILDINGDELEGATE_H
#define BUILDINGDELEGATE_H

#include <QStyledItemDelegate>

class BuildingDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    BuildingDelegate(QObject* parent = nullptr);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
};

#endif // BUILDINGDELEGATE_H
