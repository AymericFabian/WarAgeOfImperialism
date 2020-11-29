#include "historystate.h"
#include "player.h"
#include "world.h"

#include <QJsonArray>

HistoryState::HistoryState()
{
}

HistoryState::HistoryState(QDate date) : date(date)
{
    for(Player* player : World::GetInstance()->players)
        playersState.append(new PlayerState(player));
}

HistoryState::~HistoryState()
{
    for(PlayerState* ps : playersState)
        delete ps;
}

void HistoryState::write(QJsonObject &json) const
{
    json["date"] = date.toString("dd/MM/yyyy");

    QJsonArray playersArray;
    for (int i=0; i<playersState.size(); i++)
    {
        QJsonObject playerObject;
        playersState.at(i)->write(playerObject);
        playersArray.append(playerObject);
    }
    json["players"] = playersArray;
}

void HistoryState::read(const QJsonObject &json)
{
    if (json.contains("date") && json["date"].isString())
        date = QDateTime::fromString(json["date"].toString(),"dd/MM/yyyy");

    if (json.contains("players") && json["players"].isArray())
    {
        QJsonArray playersArray = json["players"].toArray();
        for(int i=0; i<playersArray.size(); i++)
        {
            PlayerState* ps = new PlayerState();
            ps->read(playersArray[i].toObject());
            playersState.append(ps);
        }
    }
}

HistoryState::PlayerState::PlayerState()
{
}

HistoryState::PlayerState::PlayerState(Player* player)
{
     income = player->income;
     countries = World::GetInstance()->GetCountriesForPlayer(player).size();

     researches = 0;
     for (int i=0; i<=(int)Player::Technology::Cavalry; i++)
         researches += player->technologies[(Player::Technology)i];

     for (int i=0; i<=(int)BuildingPrimary::Fort; i++)
         buildings[(BuildingPrimary)i] = player->buildings((BuildingPrimary)i);
}

int HistoryState::PlayerState::getAllBuildings()
{
    int total = 0;

    for (int i=0; i<=(int)BuildingPrimary::Fort; i++)
        total += buildings[(BuildingPrimary)i];

    return total;
}

void HistoryState::PlayerState::write(QJsonObject &json) const
{
    json["income"] = income;
    json["countries"] = countries;
    json["researches"] = researches;

    QJsonArray buildingsJson;
    for (int i=0; i<=(int)BuildingPrimary::Fort; i++)
        buildingsJson.append(buildings[(BuildingPrimary)i]);
    json["buildings"] = buildingsJson;
}

void HistoryState::PlayerState::read(const QJsonObject &json)
{
    if (json.contains("income") && json["income"].isDouble())
        income = json["income"].toInt();

    if (json.contains("countries") && json["countries"].isDouble())
        countries = json["countries"].toInt();

    if (json.contains("researches") && json["researches"].isDouble())
        researches = json["researches"].toInt();

    if (json.contains("buildings") && json["buildings"].isArray())
    {
        QJsonArray array = json["buildings"].toArray();
        for (int i=0; i<=(int)BuildingPrimary::Fort; i++)
            buildings[(BuildingPrimary)i] = array[i].toInt();
    }
}
