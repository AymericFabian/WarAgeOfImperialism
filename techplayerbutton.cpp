#include "techplayerbutton.h"

QList<QString> TechPlayerButton::colorNames = { "Red", "Green", "Blue", "Yellow", "Purple", "Gray" };

TechPlayerButton::TechPlayerButton(QWidget *parent) : QToolButton(parent)
{
}

void TechPlayerButton::init(Color color)
{
    this->color = color;
    QString colorName = colorNames[(int)color];

    uncheckedIcon = QIcon(":/root/techButton" + colorName + "Empty.png");
    checkedIcon = QIcon(":/root/techButton" + colorName + "Full.png");
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
