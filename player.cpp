#include "player.h"
#include "world.h"

#include <QJsonArray>

QList<QString> Player::technoNames = { "Education", "Science", "Military Academy", "Advanced Engineering", "Metallurgy", "Industry",
                                       "Inflation", "Economics", "Trade", "Government", "Artillery", "Battleship Guns", "Rifles", "Cavalry" };

Player::Player(QColor col, QString name) : color(col), name(name)
{
    enemy.append(true);
    for(int i=1; i<=6; i++)
        enemy.append(false);

    for(int i=0; i<=(int)Technology::Cavalry; i++)
        technologies[(Technology)i] = 0;
}

QString Player::getTechnoName(Technology techno)
{
    return technoNames[(int)techno];
}

void Player::write(QJsonObject& json) const
{
    json["name"] = name;
    json["income"] = income;
    json["bank"] = bank;
    json["blockades"] = blockadesCount;

    QJsonArray enemiesArray;
    for(int i=0; i<enemy.size(); i++)
        enemiesArray.append(enemy.at(i));
    json["enemy"] = enemiesArray;

    QJsonArray technosArray;
    for(int i=0; i<=(int)Technology::Cavalry; i++)
        technosArray.append(technologies[(Technology)i]);
    json["technos"] = technosArray;
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

    if (json.contains("technos") && json["technos"].isArray())
    {
        QJsonArray technosArray = json["technos"].toArray();
        for(int i=0; i<technosArray.size(); i++)
        {
            QJsonValue v = technosArray[i];
            if(v.isDouble())
                technologies[(Technology)i] = v.toInt();
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

int Player::resourceTokens()
{
    int tokens = 0;

    QList<Country*> pCountries = World::GetInstance()->GetCountriesForPlayer(this);
    for(Country* c : pCountries)
        if(c->getResource() > 0)
            tokens++;

    return tokens;
}

int Player::incomeFromBuildings(QList<Country*> countries)
{
    QList<Country*> pCountries = World::GetInstance()->GetCountriesForPlayer(this);
    int buildingIncome = 0;

    for(Country* c : countries)
    {
        switch(c->getBuildingPrim())
        {
        case BuildingPrimary::None:
            break;
        case BuildingPrimary::City:
            buildingIncome += 10 + 5 * technologies[Technology::Government];
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
                        for(int i=0; i<pCountries.size(); i++)
                            if(pCountries[i]->getPlayer() == c->getPlayer() && pCountries[i]->getResource() > 0)
                                buildingIncome += 2 + technologies[Technology::Industry];
                        break;
                    }
                }
            }

            break;
        case BuildingPrimary::Port:
            for(int i=0; i<pCountries.size(); i++)
                if(pCountries[i]->getPlayer() == c->getPlayer() && pCountries[i]->getBuildingPrim() == BuildingPrimary::Factory)
                    buildingIncome += 2 + technologies[Technology::Trade];
            for(Country* c : countries)
                if(c->getBuildingPrim() == BuildingPrimary::Port)
                    buildingIncome += 1;
            break;
        case BuildingPrimary::Railroad:
            for(Country* neighbor : c->neighbors)
            {
                if(neighbor->getPlayer() == c->getPlayer())
                {
                    if(neighbor->getBuildingPrim() == BuildingPrimary::City ||
                       neighbor->getBuildingPrim() == BuildingPrimary::Factory ||
                       neighbor->getBuildingPrim() == BuildingPrimary::Port)
                        buildingIncome += 4 + technologies[Technology::Economics];
                    if(neighbor->getResource() > 0)
                        buildingIncome += 4 + technologies[Technology::Economics];
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
