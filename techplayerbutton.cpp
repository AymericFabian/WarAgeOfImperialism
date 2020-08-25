#include "techplayerbutton.h"

QList<QString> TechPlayerButton::colorNames = { "Red", "Green", "Blue", "Yellow", "Purple", "Gray" };

TechPlayerButton::TechPlayerButton(QWidget *parent) : QToolButton(parent)
{
    setStyleSheet(QString::fromUtf8("QToolButton:disabled""{ color: white }"));
}

void TechPlayerButton::init(Color color)
{
    this->color = color;
    QString colorName = colorNames[(int)color];

    uncheckedIcon.addPixmap(QPixmap(":/root/techButton" + colorName + "Full.png"), QIcon::Normal);
    uncheckedIcon.addPixmap(QPixmap(":/root/techButton" + colorName + "Full.png"), QIcon::Disabled);
    checkedIcon.addPixmap(QPixmap(":/root/techButton" + colorName + "Full.png"), QIcon::Normal);
    checkedIcon.addPixmap(QPixmap(":/root/techButton" + colorName + "Full.png"), QIcon::Disabled);
    setIcon(uncheckedIcon);

    setCheckable(true);
    connect(this, SIGNAL(toggled(bool)), this, SLOT(onToggle(bool)));
}

void TechPlayerButton::onToggle(bool checked)
{
    if(checked)
        setIcon(checkedIcon);
    else
        setIcon(uncheckedIcon);
}
