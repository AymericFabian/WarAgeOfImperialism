#include "player.h"
#include "world.h"

#include <QJsonArray>

Player::Player(QColor col, QString name) : color(col), name(name)
{
    enemy.append(true);
    for(int i=1; i<=6; i++)
        enemy.append(false);
}

void Player::write(QJsonObject& json) const
{
    json["name"] = name;
    json["income"] = income;
    json["bank"] = bank;
    json["blockades"] = blockadesCount;


    QJsonArray enemiesArray;
    for(int i=0; i<enemy.size(); i++)
        enemiesArray.append(enemy.at(0));
    json["enemy"] = enemiesArray;
}

void Player::read(const QJsonObject &json)
{
    if (json.contains("name") && json["name"].isString())
        name = json["name"].toString();

    if (json.contains("building") && json["income"].isDouble())
        income = json["income"].toInt();

    if (json.contains("bank") && json["bank"].isDouble())
        bank = json["bank"].toInt();

    if (json.contains("blockades") && json["blockades"].isDouble())
        blockadesCount = json["blockades"].toInt();

    if (json.contains("enemy") && json["enemy"].isArray())
    {
        QJsonArray enemiesArray = json["enemy"].toArray();
        for(int i=0; i<enemiesArray.size(); i++)
        {
            QJsonValue v = enemiesArray[i];
            if(v.isBool())
                enemy[i] = v.toBool();
        }
    }
}

void Player::setBlockades(int b)
{
    blockadesCount = b;
    World::GetInstance()->calculateIncomes();
}

int Player::buildings(BuildingPrimary type)
{
    QList<Country*> countries = World::GetInstance()->GetCountriesForPlayer(this);
    return std::count_if(countries.begin(), countries.end(), [type](const Country* c) { return c->getBuildingPrim() == type; });
}

int Player::schools()
{
    QList<Country*> countries = World::GetInstance()->GetCountriesForPlayer(this);
    return std::count_if(countries.begin(), countries.end(), [](const Country* c) { return c->hasSchool(); });
}

int Player::forts()
{
    QList<Country*> countries = World::GetInstance()->GetCountriesForPlayer(this);
    return std::count_if(countries.begin(), countries.end(), [](const Country* c) { return c->hasFort(); });
}

int Player::incomeFromBuildings(QList<Country*> countries)
{
    QList<Country*> allCountries = World::GetInstance()->GetCountriesForPlayer(this);
    int buildingIncome = 0;

    for(Country* c : countries)
    {
        switch(c->getBuildingPrim())
        {
        case BuildingPrimary::None:
            break;
        case BuildingPrimary::City:
            buildingIncome += 10;
            break;
        case BuildingPrimary::Factory:
            for(Country* neighbor : c->neighbors)
            {
                if(neighbor->getPlayer() == c->getPlayer())
                {
                    // need at least 1 city adjacent to the factory for it to produce PP
                    if(neighbor->getBuildingPrim() == BuildingPrimary::City)
                    {
                        buildingIncome += 10;
                        for(int i=0; i<allCountries.size(); i++)
                            if(allCountries[i]->getPlayer() == c->getPlayer() && allCountries[i]->getResource() > 0)
                                buildingIncome += 2;
                        break;
                    }
                }
            }

            break;
        case BuildingPrimary::Port:
            for(int i=0; i<allCountries.size(); i++)
            {
                if(allCountries[i]->getPlayer() == c->getPlayer() && allCountries[i]->getBuildingPrim() == BuildingPrimary::Factory)
                    buildingIncome += 2;
                if(allCountries[i]->getBuildingPrim() == BuildingPrimary::Port)
                    buildingIncome += 1;
            }
            break;
        case BuildingPrimary::Railroad:
            for(Country* neighbor : c->neighbors)
            {
                if(neighbor->getPlayer() == c->getPlayer())
                {
                    if(neighbor->getBuildingPrim() == BuildingPrimary::City ||
                       neighbor->getBuildingPrim() == BuildingPrimary::Factory ||
                       neighbor->getBuildingPrim() == BuildingPrimary::Port)
                        buildingIncome += 4;
                    if(neighbor->getResource() > 0)
                        buildingIncome += 4;
                }
            }
            break;
        }
    }

    return buildingIncome;
}

int Player::incomeFromBuildings(BuildingPrimary type)
{
    QList<Country*> countries = World::GetInstance()->GetCountriesForPlayer(this);
    for(int i=countries.size() - 1; i>=0; i--)
        if(countries[i]->getBuildingPrim() != type)
            countries.removeAt(i);

    return incomeFromBuildings(countries);
}

int Player::incomeFromCountry(Country *c)
{
    int countryIncome = 0;
    countryIncome += c->getResource();
    countryIncome += incomeFromBuildings({c});
    return countryIncome;
}

int Player::incomeFromResources()
{
    QList<Country*> countries = World::GetInstance()->GetCountriesForPlayer(this);

    int resourcesIncome = 0;

    for(Country* c : countries)
    {
        resourcesIncome += c->getResource();
    }
    return resourcesIncome;
}
