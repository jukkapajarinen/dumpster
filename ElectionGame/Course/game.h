#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QString>

#include <memory>
#include <vector>

/**
 * @file
 * @brief Pelin stattisen tilan säilyttävä luokka
 */

namespace Interface
{

class DeckInterface;
class Location;
class Player;

/**
 * @brief Game säilyttää pelin staattisen tilan.
 *
 * Luokalle on tarkoitus asettaa ensin pelin elementit paikoilleen ja sitten
 * käynnistää peli. Luokka pitää kirjaa vuorossa olevasta pelaajasta ja siitä,
 * onko peli käynnissä, mutta vuorojen vaihtumiseen ja pelin päättymiseen
 * liittyvä logiikka on toteutettava muualla.
 *
 * Luokan kaikilla metodeilla on esiehtona, että olio on jaettujen osoittimien
 * omistuksessa.
 *
 * Jos luokan metodi ei ole poikkeustakuultaan nothrow, voi metodista aina vuotaa ulos poikkeus `std::bad_alloc` (muisti loppui).
 */
class Game: public QObject, public std::enable_shared_from_this<Game>
{
    Q_OBJECT

public:
    /**
     * @brief oletusrakentaja
     * @post pelissä ei ole pelaajia eikä alueita, ja neuvospakka on tyhjä
     */
    explicit Game();

    /**
     * @brief oletuspurkaja
     */
	virtual ~Game() = default;

    /**
     * @copydoc players()
     */
    std::vector<std::shared_ptr<const Interface::Player> > players() const;
    /**
     * @brief players palauttaa kaikki pelaajat
     * @pre -
     * @return Vektori, jossa pelin pelaajat
     * @post Poikkeustakuu: vahva
     */
    std::vector<std::shared_ptr<Interface::Player> > players();

    /**
     * @copydoc locations()
     */
    std::vector<std::shared_ptr<const Location> > locations() const;
    /**
     * @brief locations palauttaa kaikki pelilaudan alueet
     * @pre -
     * @return Vektori, jossa pelin alueet
     * @post Poikkeustakuu: vahva
     */
    std::vector<std::shared_ptr<Location> > locations();

    /**
     * @copydoc councilorDeck()
     */
    std::shared_ptr<const DeckInterface> councilorDeck() const;
    /**
     * @brief councilorDeck palauttaa neuvospakan
     * @pre -
     * @return Jaettu osoitin neuvoston jäsenet sisältävään pakkaan
     * @post Poikkeustakuu: vahva
     */
    std::shared_ptr<DeckInterface> councilorDeck();

    /**
     * @brief active palauttaa tiedon, onko peli käynnissä
     * @pre -
     * @return tosi, joss peli on käynnissä
     * @post Poikkeustakuu: nothrow
     */
    bool active() const;

    /**
     * @brief setActive käynnistää tai pysäyttää pelin
     * @pre -
     * @param active tosi, joss peli asetetaan käyntiin
     * @post peli on asetettu parametrin mukaiseen tilaan
     * @post Poikkeustakuu: nothrow
     */
    void setActive(bool active);

    /**
     * @copydoc currentPlayer()
     */
    std::shared_ptr<const Player> currentPlayer() const;
    /**
     * @brief currentPlayer kertoo vuorossa olevan pelaajan
     * @pre pelissä on ainakin yksi pelaaja
     * @return jaettu osoitin vuorossa olevaan pelaajaan
     * @post Poikkeustakuu: nothrow
     */
    std::shared_ptr<Interface::Player> currentPlayer();

    /**
     * @brief addLocation lisää peliin pelialueen
     * @pre location != nullptr
     * @param location jaettu osoitin lisättävään pelialueeseen
     * @post Pelialue lisätty peliin
     * @post Poikkeustakuu: vahva
     * @exception FormatException virhe asetusten lukemisessa (SettingsReader)
     * @exception IOException virhe asetusten lukemisessa (SettingsReader)
     * @exception KeyException alueiden maksimimäärä ei selviä asetuksista (SettingsReader)
     * @exception StateException alueiden määrä ylittää asetuksissa määritetyn maksimin
     */
    void addLocation(std::shared_ptr<Location> location);

    /**
     * @brief addPlayer lisää peliin pelaajan
     * @pre pelaajia ei ole luotu tämän luokan ulkopuolella
     * @param name lisättävän pelaajan nimi
     * @return jaettu osoitin lisättyyn pelaajaan
     * @post pelaaja lisätty peliin
     * @post Poikkeustakuu: vahva
     * @exception FormatException virhe asetusten lukemisessa (SettingsReader)
     * @exception IOException virhe asetusten lukemisessa (SettingsReader)
     * @exception KeyException pelaajien maksimimäärä ei selviä asetuksista (SettingsReader)
     * @exception StateException pelaajien määrä ylittää asetuksissa määritetyn maksimin
     */
    std::shared_ptr<Player> addPlayer(const QString& name);

    /**
     * @brief addPlayer lisää peliin pelaajan
     * @pre -
     * @param player lisättävä pelaaja
     * @post pelaaja lisätty peliin
     * @post Poikkeustakuu: vahva
     * @exception FormatException virhe asetusten lukemisessa (SettingsReader)
     * @exception IOException virhe asetusten lukemisessa (SettingsReader)
     * @exception KeyException pelaajien maksimimäärä ei selviä asetuksista (SettingsReader)
     * @exception StateException pelaajien määrä ylittää asetuksissa määritetyn maksimin
     */
    void addPlayer(std::shared_ptr<Player> player);

    /**
     * @brief nextPlayer siirtää vuoron lisäysjärjestyksessä seuraavalle pelaajalle, kiertäen tarvittaessa alkuun
     * @pre pelissä on ainakin yksi pelaaja
     * @post Vuoro on vaihtunut. Vuorossa olevan pelaajan tilan muutoksesta on signaloitu (signaali playerChanged).
     * @post Poikkeustakuu: nothrow
     */
    virtual void nextPlayer();

    /**
     * @brief notify ilmoittaa vuorossa olevan pelaajan tilan muutoksesta
     * @pre -
     * @param prevPlayer jaettu osoitin vuoronsa päättäneeseen pelaajaan, tai tyhjä osoitin (oletus) jos kyse ei ole vuoron vaihtumisesta
     * @post signaali playerChanged on lähetetty
     * @post Poikkeustakuu: nothrow
     */
    void notify(std::shared_ptr<const Player> prevPlayer = nullptr) const;

signals:
    /**
     * @brief playerChanged lähetetään, kun vuorossa olevan pelaajan tila muuttuu
     * @param actingPlayer pelaaja, jonka toiminnan seurauksena muutos tapahtui (edellinen pelaaja vuoron vaihtuessa, muuten vuorossa oleva pelaaja)
     */
    void playerChanged(std::shared_ptr<const Player> actingPlayer) const;

    /**
     * @brief councilorDeckChanged lähetetään, kun neuvospakan tila muuttuu
     */
    void councilorDeckChanged() const;

private:
    std::vector<std::shared_ptr<Player> > players_;
    std::vector<std::shared_ptr<Location> > locations_;
    std::shared_ptr<DeckInterface> councilorDeck_;

    bool active_;
    unsigned short currentPlayer_;

private slots:
    void updateCouncilors();
};

} // Interface

#endif // GAME_H
