#include "buildingdelegate.h"

#include <QComboBox>

BuildingDelegate::BuildingDelegate(QObject* parent) : QStyledItemDelegate(parent)
{
}

QWidget* BuildingDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const
{
    QStringList values;
    values << "None" << "City" << "Factory" << "Port" << "Railroad";

    QComboBox* comboBox = new QComboBox(parent);
    comboBox->addItems(values);
    return comboBox;
}

void BuildingDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox* comboBox = qobject_cast<QComboBox*>(editor);
    QString value = comboBox->currentText();
    model->setData(index, value, Qt::EditRole);
}

void BuildingDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QComboBox* comboBox = qobject_cast<QComboBox*>(editor);
    comboBox->setCurrentIndex(comboBox->findText(value));
}
