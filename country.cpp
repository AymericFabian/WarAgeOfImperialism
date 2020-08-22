#include "country.h"
#include "player.h"
#include "world.h"
#include <QDebug>

QList<QString> Country::buildingNames = {"None", "City", "Factory", "Port", "Railroad"};
QList<QString> Country::continentNames = {"Europe", "Center Asia", "Eastern Asia", "Oceania", "Middle East", "Africa"};

Country::Country(QString name, Continent cont, Player* player) : name(name), continent(cont), player(player)
{
}

BuildingPrimary Country::getBuildingType(QString build)
{
    return (BuildingPrimary) buildingNames.indexOf(build);
}

QString Country::getBuildingName(BuildingPrimary build)
{
    if((int)build > 0 && (int)build < buildingNames.size())
        return buildingNames[(int)build];
    return "None";
}

QString Country::getContinentName(Continent cont)
{
    return continentNames[(int)cont];
}

void Country::setPlayer(Player* newPlayer)
{
    player = newPlayer;
    World::GetInstance()->calculateIncomes();
}

void Country::setFort(bool fort)
{
    this->fort = fort;
}

void Country::setSchool(bool school)
{
    this->school = school;
}

void Country::setResource(int resource)
{
    this->resource = resource;
    World::GetInstance()->calculateIncomes();
}

void Country::setBuilding(BuildingPrimary building)
{
    this->buildingPrim = building;
    World::GetInstance()->calculateIncomes();
}

const QColor Country::getColor() const
{
    switch(continent)
    {
    case Continent::Europe:
        return QColor::fromRgb(80,230,10);
    case Continent::CenterAsia:
        return QColor::fromRgb(255,71,26);
    case Continent::EastAsia:
        return QColor::fromRgb(0,204,102);
    case Continent::Oceania:
        return QColor::fromRgb(255,204,0);
    case Continent::MiddleEast:
        return QColor::fromRgb(255,255,26);
    case Continent::Africa:
        return QColor::fromRgb(236,179,255);
    }
    return QColor(Qt::white);
}
