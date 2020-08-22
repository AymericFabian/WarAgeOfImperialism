#include "world.h"
#include "player.h"

World* World::instance = nullptr;

World::World()
{
    Country* gb = new Country("Great Britain", Continent::Europe);
    Country* fr = new Country("France", Continent::Europe);
    Country* spain = new Country("Spain", Continent::Europe);
    Country* ger = new Country("Germany", Continent::Europe);
    Country* it = new Country("Italy", Continent::Europe);
    Country* prussia = new Country("Prussia", Continent::Europe);
    Country* hun = new Country("Austria Hungary", Continent::Europe);
    Country* balk = new Country("The Balkans", Continent::Europe);
    Country* lithuana = new Country("Lithuana", Continent::Europe);
    Country* scand = new Country("Scandinavia", Continent::Europe);
    Country* ukr = new Country("Ukraine", Continent::Europe);
    Country* cauca = new Country("Caucasus", Continent::Europe);
    Country* ru = new Country("Russia", Continent::Europe);

    Country* transUral = new Country("Trans-Ural", Continent::CenterAsia);
    Country* turkestan = new Country("Turkestan", Continent::CenterAsia);
    Country* afghanistan = new Country("Afghanistan", Continent::CenterAsia);
    Country* kazakhstan = new Country("Kazakhstan", Continent::CenterAsia);
    Country* india = new Country("India", Continent::CenterAsia);
    Country* siberia = new Country("Siberia", Continent::CenterAsia);
    Country* kashmir = new Country("Kashmir", Continent::CenterAsia);
    Country* tibet = new Country("Tibet", Continent::CenterAsia);
    Country* bengal = new Country("Bengal", Continent::CenterAsia);

    Country* yakut = new Country("Yakut", Continent::EastAsia);
    Country* kamchatka = new Country("Kamchatka", Continent::EastAsia);
    Country* buryat = new Country("Buryat", Continent::EastAsia);
    Country* manchuria = new Country("Manchuria", Continent::EastAsia);
    Country* mongolia = new Country("Mongolia", Continent::EastAsia);
    Country* korea = new Country("Korea", Continent::EastAsia);
    Country* japan = new Country("Japan", Continent::EastAsia);
    Country* china = new Country("China", Continent::EastAsia);
    Country* siam = new Country("Siam", Continent::EastAsia);
    Country* annam = new Country("Annam", Continent::EastAsia);

    Country* philippines = new Country("Philippines", Continent::Oceania);
    Country* sumatra = new Country("Sumatra", Continent::Oceania);
    Country* borneo = new Country("Borneo", Continent::Oceania);
    Country* newGuinea = new Country("New Guinea", Continent::Oceania);
    Country* westAus = new Country("Western Australia", Continent::Oceania);
    Country* northTerr = new Country("Northern Territory", Continent::Oceania);
    Country* southAus = new Country("South Australia", Continent::Oceania);
    Country* queensland = new Country("Queensland", Continent::Oceania);
    Country* newSouthWales = new Country("New South Wales", Continent::Oceania);

    Country* morocco = new Country("Morocco", Continent::MiddleEast);
    Country* algeria = new Country("Algeria", Continent::MiddleEast);
    Country* tripoli = new Country("Tripoli", Continent::MiddleEast);
    Country* egypt = new Country("Egypt", Continent::MiddleEast);
    Country* palestine = new Country("Palestine", Continent::MiddleEast);
    Country* ottoman = new Country("Ottoman", Continent::MiddleEast);
    Country* arabia = new Country("Arabia", Continent::MiddleEast);
    Country* mesopotamia = new Country("Mesopotamia", Continent::MiddleEast);
    Country* persia = new Country("Persia", Continent::MiddleEast);

    Country* mauritania = new Country("Mauritania", Continent::Africa);
    Country* westAfrica = new Country("West Africa", Continent::Africa);
    Country* eqAfrica = new Country("Equatorial Africa", Continent::Africa);
    Country* sudan = new Country("Sudan", Continent::Africa);
    Country* nigeria = new Country("Nigeria", Continent::Africa);
    Country* kongo = new Country("Kongo", Continent::Africa);
    Country* abyssinia = new Country("Abyssinia", Continent::Africa);
    Country* kenya = new Country("Kenya", Continent::Africa);
    Country* angola = new Country("Angola", Continent::Africa);
    Country* natu = new Country("Natu", Continent::Africa);
    Country* tanganikya = new Country("Tanganikya", Continent::Africa);
    Country* mozambique = new Country("Mozambique", Continent::Africa);
    Country* madagascar = new Country("Madagascar", Continent::Africa);

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

    countries << *gb << *fr << *spain << *ger << *it << *prussia << *hun << *balk << *lithuana << *scand << *ru << *ukr << *cauca
              << *transUral << *turkestan << *afghanistan << *siberia << *kazakhstan << *kashmir << *india << *tibet << *bengal
              << *yakut << *kamchatka << *buryat << *manchuria << *mongolia << *korea << *china << *japan << *siam << *annam
              << *sumatra << *borneo << *philippines << *newGuinea << *westAus << *northTerr << *southAus << *queensland << *newSouthWales
              << *morocco << *algeria << *tripoli << *egypt << *palestine << *ottoman << *mesopotamia << *persia << *arabia
              << *mauritania << *westAfrica << *nigeria << *eqAfrica << *sudan << *abyssinia << *kongo << *kenya << *angola << *tanganikya << *mozambique << *natu << *madagascar;

    std::sort(countries.begin(), countries.end(), [](const Country& c1, const Country& c2) {
        QString cont1 = Country::getContinentName(c1.getContinent());
        QString cont2 = Country::getContinentName(c2.getContinent());
        if(cont1 != cont2) return cont1 < cont2;
        else return c1.getName() < c2.getName();
    });


    Player* native = new Player(QColor::fromRgb(255,255,220), "Natives");
    Player* red = new Player(QColor::fromRgb(238,17,17), "Red");
    Player* green = new Player(QColor::fromRgb(0,153,0), "Green");
    Player* blue = new Player(QColor::fromRgb(0,0,204), "Blue");
    Player* yellow = new Player(QColor::fromRgb(255,240,15), "Yellow");
    Player* purple = new Player(QColor::fromRgb(153,0,204), "Purple");
    Player* grey = new Player(QColor::fromRgb(190,190,190), "Grey");

    players << native << red << green << blue << yellow << purple << grey;

    for(Country& c : countries) c.setPlayer(players.at(0));

}

World *World::GetInstance()
{
    if(!instance)
        instance = new World();

    return instance;
}

QList<Country> World::GetCountriesForPlayer(Player* player)
{
    QList<Country> countriesForPlayer;

    for(Country c : countries)
        if(c.getPlayer() == player)
            countriesForPlayer.append(c);

    return countriesForPlayer;
}
