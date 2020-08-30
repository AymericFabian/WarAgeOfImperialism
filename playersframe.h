#ifndef PLAYERSFRAME_H
#define PLAYERSFRAME_H

#include <QFrame>
#include <QTableView>

#include <QStyledItemDelegate>
#include <QLineEdit>

#include "playerstablemodel.h"

namespace Ui {
class PlayersFrame;
}

class PlayersFrame : public QFrame
{
    Q_OBJECT

public:
    explicit PlayersFrame(QWidget *parent = nullptr);
    ~PlayersFrame();

private:
    Ui::PlayersFrame *ui;

    PlayersTableModel* playersTableModel;

    class PlayerDelegate : public QStyledItemDelegate
    {
    public:
        PlayerDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}
        void setEditorData(QWidget *editor, const QModelIndex &index) const
        {
            QString value = index.model()->data(index, Qt::DisplayRole).toString();
            QLineEdit* lineEdit = qobject_cast<QLineEdit*>(editor);
            lineEdit->setText(value);
        }
    };
};

#endif // PLAYERSFRAME_H
