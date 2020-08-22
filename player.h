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
    int income;
    int bank;
    int blockadesCount;
};

#endif // PLAYER_H
