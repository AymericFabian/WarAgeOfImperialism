#include "world.h"
#include "player.h"
#include "historystate.h"

#include <QDebug>
#include <QtMath>
#include <QJsonArray>

World* World::instance = nullptr;

World::World()
{
    Player* native = new Player(QColor::fromRgb(255,255,220), "Natives");
    Player* red = new Player(QColor::fromRgb(238,17,17), "Red");
    Player* green = new Player(QColor::fromRgb(0,153,0), "Green");
    Player* blue = new Player(QColor::fromRgb(0,0,204), "Blue");
    Player* yellow = new Player(QColor::fromRgb(255,240,15), "Yellow");
    Player* purple = new Player(QColor::fromRgb(153,0,204), "Purple");
    Player* grey = new Player(QColor::fromRgb(190,190,190), "Grey");

    players << native << red << green << blue << yellow << purple << grey;

    Country* gb = new Country("Great Britain", Continent::Europe, native);
    Country* fr = new Country("France", Continent::Europe, native);
    Country* spain = new Country("Spain", Continent::Europe, native);
    Country* ger = new Country("Germany", Continent::Europe, native);
    Country* it = new Country("Italy", Continent::Europe, native);
    Country* prussia = new Country("Prussia", Continent::Europe, native);
    Country* hun = new Country("Austria Hungary", Continent::Europe, native);
    Country* balk = new Country("The Balkans", Continent::Europe, native);
    Country* lithuana = new Country("Lithuana", Continent::Europe, native);
    Country* scand = new Country("Scandinavia", Continent::Europe, native);
    Country* ukr = new Country("Ukraine", Continent::Europe, native);
    Country* cauca = new Country("Caucasus", Continent::Europe, native);
    Country* ru = new Country("Russia", Continent::Europe, native);

    Country* transUral = new Country("Trans-Ural", Continent::CenterAsia, native);
    Country* turkestan = new Country("Turkestan", Continent::CenterAsia, native);
    Country* afghanistan = new Country("Afghanistan", Continent::CenterAsia, native);
    Country* kazakhstan = new Country("Kazakhstan", Continent::CenterAsia, native);
    Country* india = new Country("India", Continent::CenterAsia, native);
    Country* siberia = new Country("Siberia", Continent::CenterAsia, native);
    Country* kashmir = new Country("Kashmir", Continent::CenterAsia, native);
    Country* tibet = new Country("Tibet", Continent::CenterAsia, native);
    Country* bengal = new Country("Bengal", Continent::CenterAsia, native);

    Country* yakut = new Country("Yakut", Continent::EastAsia, native);
    Country* kamchatka = new Country("Kamchatka", Continent::EastAsia, native);
    Country* buryat = new Country("Buryat", Continent::EastAsia, native);
    Country* manchuria = new Country("Manchuria", Continent::EastAsia, native);
    Country* mongolia = new Country("Mongolia", Continent::EastAsia, native);
    Country* korea = new Country("Korea", Continent::EastAsia, native);
    Country* japan = new Country("Japan", Continent::EastAsia, native);
    Country* china = new Country("China", Continent::EastAsia, native);
    Country* siam = new Country("Siam", Continent::EastAsia, native);
    Country* annam = new Country("Annam", Continent::EastAsia, native);

    Country* philippines = new Country("Philippines", Continent::Oceania, native);
    Country* sumatra = new Country("Sumatra", Continent::Oceania, native);
    Country* borneo = new Country("Borneo", Continent::Oceania, native);
    Country* newGuinea = new Country("New Guinea", Continent::Oceania, native);
    Country* westAus = new Country("Western Australia", Continent::Oceania, native);
    Country* northTerr = new Country("Northern Territory", Continent::Oceania, native);
    Country* southAus = new Country("South Australia", Continent::Oceania, native);
    Country* queensland = new Country("Queensland", Continent::Oceania, native);
    Country* newSouthWales = new Country("New South Wales", Continent::Oceania, native);

    Country* morocco = new Country("Morocco", Continent::MiddleEast, native);
    Country* algeria = new Country("Algeria", Continent::MiddleEast, native);
    Country* tripoli = new Country("Tripoli", Continent::MiddleEast, native);
    Country* egypt = new Country("Egypt", Continent::MiddleEast, native);
    Country* palestine = new Country("Palestine", Continent::MiddleEast, native);
    Country* ottoman = new Country("Ottoman", Continent::MiddleEast, native);
    Country* arabia = new Country("Arabia", Continent::MiddleEast, native);
    Country* mesopotamia = new Country("Mesopotamia", Continent::MiddleEast, native);
    Country* persia = new Country("Persia", Continent::MiddleEast, native);

    Country* mauritania = new Country("Mauritania", Continent::Africa, native);
    Country* westAfrica = new Country("West Africa", Continent::Africa, native);
    Country* eqAfrica = new Country("Equatorial Africa", Continent::Africa, native);
    Country* sudan = new Country("Sudan", Continent::Africa, native);
    Country* nigeria = new Country("Nigeria", Continent::Africa, native);
    Country* kongo = new Country("Kongo", Continent::Africa, native);
    Country* abyssinia = new Country("Abyssinia", Continent::Africa, native);
    Country* kenya = new Country("Kenya", Continent::Africa, native);
    Country* angola = new Country("Angola", Continent::Africa, native);
    Country* natu = new Country("Natu", Continent::Africa, native);
    Country* tanganikya = new Country("Tanganikya", Continent::Africa, native);
    Country* mozambique = new Country("Mozambique", Continent::Africa, native);
    Country* madagascar = new Country("Madagascar", Continent::Africa, native);

    fr->neighbors << spain << ger << it;
    spain->neighbors << fr;
    ger->neighbors << fr << it << prussia << hun;
    it->neighbors << fr << ger << hun;
    prussia->neighbors << ger << hun << ukr << lithuana;
    hun->neighbors << it << ger << prussia << ukr << balk;
    balk->neighbors << hun << ukr;
    lithuana->neighbors << ru << ukr << hun;
    ukr->neighbors << prussia << hun << balk << cauca << ru << lithuana;
    scand->neighbors << ru;
    ru->neighbors << scand << lithuana << ukr << cauca << transUral;
    cauca->neighbors << ru << ukr << ottoman << mesopotamia << turkestan << transUral;

    transUral->neighbors << ru << cauca << turkestan << kazakhstan << siberia;
    turkestan->neighbors << cauca << persia << afghanistan << kazakhstan << transUral;
    afghanistan->neighbors << turkestan << persia << india << kashmir << kazakhstan;
    india->neighbors << persia << afghanistan << kashmir << tibet << bengal;
    siberia->neighbors << transUral << kazakhstan << china << mongolia << buryat << yakut;
    kazakhstan->neighbors << transUral << turkestan << afghanistan << kashmir << china << siberia;
    kashmir->neighbors << afghanistan << india << tibet << china << kazakhstan;
    tibet->neighbors << kashmir << india << bengal << china;
    bengal->neighbors << tibet << india << siam << china;

    yakut->neighbors << siberia << buryat << kamchatka;
    kamchatka->neighbors << yakut << buryat << manchuria;
    buryat->neighbors << siberia << mongolia << manchuria << kamchatka << yakut;
    mongolia->neighbors << siberia << china << manchuria << buryat;
    manchuria->neighbors << kamchatka << buryat << mongolia << china << korea;

    korea->neighbors << manchuria;
    china->neighbors << manchuria << mongolia << siberia << kazakhstan << kashmir << tibet << bengal << siam << annam;
    siam->neighbors << annam << china << bengal;
    annam->neighbors << china << siam;

    westAus->neighbors << northTerr << southAus;
    northTerr->neighbors << westAus << southAus << queensland;
    southAus->neighbors << westAus << northTerr << queensland << newSouthWales;
    queensland->neighbors << northTerr << southAus << newSouthWales;
    newSouthWales->neighbors << southAus << queensland;

    morocco->neighbors << algeria << mauritania;
    algeria->neighbors << morocco << mauritania << westAfrica << tripoli;
    tripoli->neighbors << algeria << westAfrica << eqAfrica << sudan << egypt;
    egypt->neighbors << tripoli << sudan << palestine;
    palestine->neighbors << egypt << arabia << mesopotamia << ottoman;
    ottoman->neighbors << balk << palestine << mesopotamia << cauca;
    mesopotamia->neighbors << cauca << ottoman << palestine << arabia << persia;
    persia->neighbors << mesopotamia << turkestan << afghanistan << india;
    arabia->neighbors << palestine << mesopotamia;

    mauritania->neighbors << morocco << algeria << westAfrica << nigeria;
    westAfrica->neighbors << algeria << mauritania << nigeria << eqAfrica << tripoli;
    nigeria->neighbors << mauritania << westAfrica << eqAfrica << kongo;
    eqAfrica->neighbors << tripoli << westAfrica << nigeria << kongo << sudan;
    sudan->neighbors << egypt << tripoli << eqAfrica << kongo << kenya << abyssinia;
    abyssinia->neighbors << sudan << kenya;
    kongo->neighbors << nigeria << eqAfrica << sudan << kenya << tanganikya << angola;
    kenya->neighbors << abyssinia << sudan << kongo << tanganikya;
    angola->neighbors << kongo << tanganikya << mozambique << natu;
    tanganikya->neighbors << kenya << kongo << angola << mozambique;
    mozambique->neighbors << tanganikya << angola << natu;
    natu->neighbors << angola << mozambique;

    countries << gb << fr << spain << ger << it << prussia << hun << balk << lithuana << scand << ru << ukr << cauca
              << transUral << turkestan << afghanistan << siberia << kazakhstan << kashmir << india << tibet << bengal
              << yakut << kamchatka << buryat << manchuria << mongolia << korea << china << japan << siam << annam
              << sumatra << borneo << philippines << newGuinea << westAus << northTerr << southAus << queensland << newSouthWales
              << morocco << algeria << tripoli << egypt << palestine << ottoman << mesopotamia << persia << arabia
              << mauritania << westAfrica << nigeria << eqAfrica << sudan << abyssinia << kongo << kenya << angola << tanganikya << mozambique << natu << madagascar;

    std::sort(countries.begin(), countries.end(), [](const Country* c1, const Country* c2) {
        QString cont1 = Country::getContinentName(c1->getContinent());
        QString cont2 = Country::getContinentName(c2->getContinent());
        if(cont1 != cont2) return cont1 < cont2;
        else return c1->getName() < c2->getName();
    });
}

World::~World()
{
    for(Country* c : countries)
        delete c;
    for(Player* p : players)
        delete p;
    for(HistoryState* hs : history)
        delete hs;
}

void World::write(QJsonObject& json) const
{
    QJsonArray playersArray;
    for(Player* p : players)
    {
        QJsonObject playerObject;
        p->write(playerObject);
        playersArray.append(playerObject);
    }
    json["players"] = playersArray;

    QJsonArray countriesArray;
    for(Country* c : countries)
    {
        QJsonObject countryObject;
        c->write(countryObject);
        countriesArray.append(countryObject);
    }
    json["countries"] = countriesArray;

    QJsonArray historyArray;
    for(HistoryState* hs : history)
    {
        QJsonObject histo;
        hs->write(histo);
        historyArray.append(histo);
    }
    json["history"] = historyArray;
}

void World::read(const QJsonObject &json)
{
    if (json.contains("players") && json["players"].isArray()) {
        QJsonArray playersArray = json["players"].toArray();
        for (int playerIdx = 0; playerIdx < playersArray.size(); playerIdx++) {
            QJsonObject playerObject = playersArray[playerIdx].toObject();
            players[playerIdx]->read(playerObject);
        }
    }

    if (json.contains("countries") && json["countries"].isArray()) {
        QJsonArray countriesArray = json["countries"].toArray();
        for (int countryIdx = 0; countryIdx < countriesArray.size(); countryIdx++) {
            QJsonObject countryObject = countriesArray[countryIdx].toObject();
            for(Country* c : countries)
                if(c->getName() == countryObject["name"].toString())
                    c->read(countryObject);
        }
    }

    for(HistoryState* hs : history)
        delete hs;
    history.clear();

    if (json.contains("history") && json["history"].isArray()) {
        QJsonArray historyArray = json["history"].toArray();
        for (int histoIdx = 0; histoIdx < historyArray.size(); histoIdx++) {
            HistoryState* hs = new HistoryState();
            hs->read(historyArray[histoIdx].toObject());
            history.append(hs);
        }
    }

    calculateIncomes();
}

World *World::GetInstance()
{
    if(!instance)
        instance = new World();

    return instance;
}

Player* World::getPlayerByName(QString name)
{
    for(Player* p : players)
        if(p->name == name)
            return p;
    return nullptr;
}

void World::calculateIncomes()
{
    for(Player* p : players)
    {
        p->income = 0;
        QList<Country*> playerCountries = GetCountriesForPlayer(p);

        for(Country* c : playerCountries)
        {
            p->income += p->incomeFromCountry(c);
        }
    }

    for(int i=0; i <= (int)Continent::Africa; i++)
    {
        Player* owner = nullptr;
        bool isUnited = true;

        for(Country* c : countries)
        {
            if((int)(c->getContinent()) == i)
            {
                if(owner == nullptr)
                    owner = c->getPlayer();

                if(c->getPlayer() != owner)
                {
                    isUnited = false;
                    break;
                }
            }
        }
        if(isUnited)
            owner->income += 30;
    }

    double inflation = 1;
    for(Player* p : players)
        if(p->technologies[Player::Technology::Inflation] + 1 > inflation)
            inflation = p->technologies[Player::Technology::Inflation] + 1;

    for(Player* p : players)
        p->income = qRound(p->income / inflation);

    for(Player* p : players)
        p->income -= qRound((double)qMin(p->blockades() * 10, p->income/2));
}

QList<Country*> World::GetCountriesForPlayer(Player* player)
{
    QList<Country*> countriesForPlayer;

    for(Country* c : countries)
        if(c->getPlayer() == player)
            countriesForPlayer.append(c);

    return countriesForPlayer;
}

void World::ResearchTech(int player, Player::Technology techno, int level, bool researched)
{
    if(researched)
        players[player]->technologies[techno] = level;
    else
        players[player]->technologies[techno] = level - 1;
    calculateIncomes();
}

HistoryState* World::saveState()
{
    QDate firstDate(1886,1,15);
    HistoryState* hs = new HistoryState(firstDate.addMonths(history.size()));
    history.append(hs);
    return hs;
}

void World::deleteState()
{
    if(history.empty()) return;

    HistoryState* hs = history.last();
    history.removeLast();
    delete hs;
}
