#ifndef TECHPLAYERBUTTON_H
#define TECHPLAYERBUTTON_H

#include <QToolButton>

#include "player.h"

class TechPlayerButton : public QToolButton
{
    Q_OBJECT
public:
    enum class Color {Red, Green, Blue, Yellow, Purple, Gray};

    TechPlayerButton(QWidget* parent = nullptr);

    QIcon checkedIcon;
    QIcon uncheckedIcon;

    void init(Color color);
    Color color;

private slots:
    void onToggle(bool checked);

private:
    static QList<QString> colorNames;
};

#endif // TECHPLAYERBUTTON_H
