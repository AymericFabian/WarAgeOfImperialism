#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QColor>

#include "country.h"

class Player
{
public:
    Player(QColor col, QString name);

    QColor color;
    QString name;
    int income = 0;
    int bank = 0;
    int resources = 0;
    int blockadesCount = 0;
};

#endif // PLAYER_H
