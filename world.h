#ifndef WORLD_H
#define WORLD_H

#include "country.h"
#include "player.h"

#include <QList>
#include <QJsonObject>

class HistoryState;

class World
{
public:
    static World* GetInstance();

    QList<Country*> GetCountriesForPlayer(Player *player);
    QList<Country*> countries;
    QList<Player*> players;
    QList<HistoryState*> history;

    Player *getPlayerByName(QString name);

    void calculateIncomes();

    void write(QJsonObject &json) const;
    void read(const QJsonObject &json);
    void ResearchTech(int player, Player::Technology techno, int level, bool researched);

    HistoryState* saveState();
    void deleteState();

private:
    World();
    ~World();
    static World* instance;

signals:
    void dataChanged();
};

#endif // WORLD_H
