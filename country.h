#ifndef COUNTRY_H
#define COUNTRY_H

#include <QList>
#include <QColor>
#include <QJsonObject>

class Player;

enum class BuildingPrimary { None, City, Factory, Port, Railroad, School, Fort };
enum class Continent { Europe, CenterAsia, EastAsia, Oceania, MiddleEast, Africa };

inline uint qHash(BuildingPrimary key, uint seed) { return ::qHash(static_cast<int>(key), seed); }

class Country
{
public:
    Country(QString name, Continent cont, Player* player);
    QList<Country*> neighbors;

    Continent getContinent() const {return continent;}
    void setPlayer(Player* newPlayer);
    void setFort(bool fort);
    void setSchool(bool school);
    void setResource(int resource);
    void setBuilding(BuildingPrimary building);

    bool hasSchool() const {return school;}
    bool hasFort() const {return fort;}
    const QColor getColor() const;
    const QString getName() const {return name;}
    const Player* getPlayer() const {return player;}
    Player* getPlayer() {return player;}
    const BuildingPrimary& getBuildingPrim() const {return buildingPrim;}
    int getResource() const {return resource;}

    static BuildingPrimary getBuildingType(QString build);
    static QString getBuildingName(BuildingPrimary build);
    static QString getContinentName(Continent cont);

    void write(QJsonObject &json) const;
    void read(const QJsonObject &json);
private:
    QString name;
    Continent continent;
    Player* player = nullptr;
    int resource = 0;
    BuildingPrimary buildingPrim = BuildingPrimary::None;
    bool school = false;
    bool fort = false;

    static QList<QString> buildingNames;
    static QList<QString> continentNames;
};

#endif // COUNTRY_H
