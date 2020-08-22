#include "playerdelegate.h"
#include "world.h"
#include "player.h"

#include <QComboBox>

PlayerDelegate::PlayerDelegate(QObject* parent) : QStyledItemDelegate(parent)
{
}

QWidget* PlayerDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const
{
    QStringList values;
    for(Player* p : World::GetInstance()->players)
        values << p->name;

    QComboBox* comboBox = new QComboBox(parent);
    comboBox->addItems(values);
    return comboBox;
}

void PlayerDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox* comboBox = qobject_cast<QComboBox*>(editor);
    QString value = comboBox->currentText();
    model->setData(index, value, Qt::EditRole);
}

void PlayerDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QComboBox* comboBox = qobject_cast<QComboBox*>(editor);
    comboBox->setCurrentIndex(comboBox->findText(value));
}
