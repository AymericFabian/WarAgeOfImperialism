#ifndef HISTORYSTATE_H
#define HISTORYSTATE_H

#include <QDate>
#include <QHash>
#include <QJsonObject>

#include "country.h"

class HistoryState
{
public:
    class PlayerState
    {
    public:
        PlayerState();
        PlayerState(Player* player);
        int getIncome(){return income;}
        int getCountries() {return countries;}
        int getResearches() {return researches;}
        int getBuildingsOfType(BuildingPrimary type) {return buildings[type];}
        int getAllBuildings();

        void write(QJsonObject &json) const;
        void read(const QJsonObject &json);

    private:
        int income;
        int countries;
        int researches;
        QHash<BuildingPrimary, int> buildings;
    };

    HistoryState();
    HistoryState(QDate date);
    ~HistoryState();

    QDateTime date;
    QList<PlayerState*> playersState;

    void write(QJsonObject &json) const;
    void read(const QJsonObject &json);
};

#endif // HISTORYSTATE_H
