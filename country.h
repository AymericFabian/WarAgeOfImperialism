#ifndef COUNTRY_H
#define COUNTRY_H

#include <QList>
#include <QColor>

class Player;

enum class BuildingPrimary { None, City, Factory, Port, Railroad };
enum class BuildingSecondary { None, School, Fort };
enum class Continent { Europe, CenterAsia, EastAsia, Oceania, MiddleEast, Africa };

class Country
{
public:
    Country(QString name, Continent cont);
    QList<Country*> neighbors;

    Continent getContinent() const {return continent;}
    const QString getName() const {return name;}
    void setPlayer(Player* newPlayer);
    const Player* getPlayer() const {return player;}
    const BuildingPrimary& getBuildingPrim() const {return buildingPrim;}
    const BuildingSecondary& getBuildingSec() const {return buildingSec;}
    int getResource() const {return resource;}
    const QColor getColor() const;

    static QString getContinentName(Continent cont);

private:
    QString name;
    Continent continent;
    Player* player = nullptr;
    int resource = 0;
    BuildingPrimary buildingPrim = BuildingPrimary::None;
    BuildingSecondary buildingSec = BuildingSecondary::None;

    static QList<QString> continentNames;
};

#endif // COUNTRY_H
