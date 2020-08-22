#ifndef WORLD_H
#define WORLD_H

#include "country.h"

#include <QList>

class World
{
public:
    static World* GetInstance();

    QList<Country> GetCountriesForPlayer(Player *player);
    QList<Country> countries;

    QList<Player*> players;

private:
    World();
    static World* instance;
};

#endif // WORLD_H