#ifndef PLAYERDELEGATE_H
#define PLAYERDELEGATE_H

#include <QStyledItemDelegate>

class PlayerDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    PlayerDelegate(QObject* parent = nullptr);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
};

#endif // PLAYERDELEGATE_H
