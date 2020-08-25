#ifndef PLAYER_H
#define PLAYER_H

#include <QHash>
#include <QString>
#include <QColor>
#include <QJsonObject>

#include "country.h"

class Player
{
public:
    enum class Technology { Education, Science, MilitaryAcademy, AdvancedEngineering, Metallurgy, Industry,
                            Inflation, Economics, Trade, Government, Artillery, BattleshipGuns, Rifles, Cavalry };

    Player(QColor col, QString name);

    QColor color;
    QString name;
    int income = 0;
    int bank = 0;
    QList<bool> enemy;
    QHash<Technology, int> technologies;
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

    static QString getTechnoName(Technology techno);
    int resourceTokens();
private:
    int blockadesCount = 0;
    static QList<QString> technoNames;
};

inline uint qHash(Player::Technology key, uint seed) { return ::qHash(static_cast<int>(key), seed); }

#endif // PLAYER_H
