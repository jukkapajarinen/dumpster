#ifndef COUNCILOR_H
#define COUNCILOR_H

#include "cardinterface.h"

/**
 * @file
 * @brief Neuvoston jäseniä kuvaavat kortit määrittelevä luokka
 */
namespace Interface
{

/**
 * @brief Councilor toteuttaa neuvoston jäseniä kuvaavat kortit.
 * Perii CardInterfacen eli sisältää myös sen.
 *
 * Jos luokan metodi ei ole poikkeustakuultaan nothrow, voi metodista aina vuotaa ulos poikkeus `std::bad_alloc` (muisti loppui).
 */
class Councilor : public CardInterface
{
public:

    /**
     * @brief Councilor rakentaja
     * @pre location != nullptr
     * @param name neuvoksen nimi
     * @param title neuvoksen arvonimi
     * @param location pelilaudan alue, jonka neuvos on kyseessä
     * @post Vaikutusvaltakortilla on annetut nimi, arvonimi ja alue, ja ei omistajaa tai pelaajaa
     */
    explicit Councilor(const QString& name, const QString& title, std::weak_ptr<Location> location);

    /**
     * @brief oletusarvoinen virtuaalipurkaja
     */
	virtual ~Councilor() = default;

    /**
     * @brief typeName palauttaa kortin tyypin
     * @pre -
     * @return Kortin tyyppi merkkijonona
     * @post Poikkeustakuu: nothrow
     */
    virtual QString typeName() const;

    /**
     * @brief name
     * @pre -
     * @return palauttaa neuvoksen nimen
     * @post Poikkeustakuu: nothrow
     */
    QString name() const;

    /**
     * @brief title
     * @pre -
     * @return palauttaa neuvoksen arvonimen
     * @post Poikkeustakuu: nothrow
     */
    QString title() const;

    /**
     * @brief location kertoo, minkä pelialueen neuvos on kyseessä
     * @pre -
     * @return heikko osoitin pelialueelle, jonka neuvos on kyseessä
     * @post Poikkeustakuu: nothrow
     */
    std::weak_ptr<Location> location() const;

    /**
     * @brief owner kertoo pelaajan, joka omistaa kortin
     * @pre -
     * @return heikko osoitin kortin omistavaan pelaajaan, tai tyhjä osoitin jos sitä ei omista kukaan
     * @post Poikkeustakuu: nothrow
     */
    std::weak_ptr<Player> owner() const;

    /**
     * @brief setOwner asettaa kortille omistajan
     * @pre -
     * @param owner heikko osoitin kortin omistajaan, tai tyhjä osoitin jos sitä ei omista kukaan
     * @post Kortilla on uusi omistaja
     * @post Poikkeustakuu: nothrow
     */
    void setOwner(std::weak_ptr<Player> owner);

    /**
     * @copydoc player()
     */
    std::weak_ptr<const Player> player() const;
    /**
     * @brief player palauttaa pelaajan, jolla on pelissä tämän neuvoston jäsenen rooli
     * @pre -
     * @return heikko osoitin pelaajaan, jolla on pelissä tämän neuvoston jäsenen rooli, tai tyhjä osoitin jos kellään pelaajalla ei sitä ole
     * @post Poikkeustakuu: nothrow
     */
    std::weak_ptr<Player> player();

    /**
     * @brief setPlayer asettaa pelaajan neuvoston jäsenen rooliin
     * @pre -
     * @param player pelaaja, tai tyhjä osoitin jos rooli jätetään vapaaksi
     * @post pelaaja on asetettu tämän neuvoksen rooliin
     * @post Poikkeustakuu: nothrow
     */
    void setPlayer(std::weak_ptr<Player> player);

private:
    const QString name_;
    const QString title_;
    const std::weak_ptr<Location> location_;

    std::weak_ptr<Player> owner_;
    std::weak_ptr<Player> player_;
};

} // Interface

#endif // COUNCILOR_H
