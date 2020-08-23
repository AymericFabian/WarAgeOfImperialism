#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QColor>
#include <QJsonObject>

#include "country.h"

class Player
{
public:
    Player(QColor col, QString name);

    QColor color;
    QString name;
    int income = 0;
    int bank = 0;
    QList<bool> enemy;
    void setBlockades(int b);

    int blockades() { return blockadesCount; }
    int schools();
    int forts();
    int buildings(BuildingPrimary type);
    int incomeFromBuildings(QList<Country *> countries);
    int incomeFromBuildings(BuildingPrimary type);
    int incomeFromCountry(Country* c);
    int incomeFromResources();

    void write(QJsonObject &json) const;
    void read(const QJsonObject &json);

private:
    int blockadesCount = 0;
};

#endif // PLAYER_H
