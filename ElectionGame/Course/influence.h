#ifndef INFLUENCE_H
#define INFLUENCE_H

#include "cardinterface.h"

/**
 * @file
 * @brief Vaikutusvaltakortit määrittävä luokka
 */

namespace Interface
{

/**
 * @brief Influence toteuttaa vaikutusvaltakortit.
 * Influence on periytetty CardInterface-rajapinnasta, eli sisältää myös senkin.
 *
 * Jos luokan metodi ei ole poikkeustakuultaan nothrow, voi metodista aina vuotaa ulos poikkeus `std::bad_alloc` (muisti loppui).
 */
class Influence : public CardInterface
{
public:
    /**
     * @brief Influence rakentaja
     * @pre -
     * @param name kortin nimi
     * @param location pelilaudan alue, jonka pakkaan kortti kuuluu
     * @param amount vaikutusvallan määrä
     * @post Vaikutusvaltakortilla on annetut nimi, alue ja vaikutusvalta, tyhjä arvonimi, ja ei omistajaa
     */
    explicit Influence(const QString& name, std::weak_ptr<Location> location, unsigned short amount);

    /**
     * @brief oletusarvoinen virtuaalipurkaja
     */
    virtual ~Influence() = default;

    /**
     * @brief typeName palauttaa kortin tyypin
     * @pre -
     * @return Kortin tyyppi merkkijonona
     * @post Poikkeustakuu: nothrow
     */
    virtual QString typeName() const;

    /*!
     * @brief name palauttaa kortin nimen
     * @pre -
     * @return Kortin nimi merkkijonona
     * @post Poikkeustakuu: nothrow
     */
    QString name() const;

    /*!
     * @brief title palauttaa kortin arvonimen
     * @pre -
     * @return Kortin arvonimi merkkijonona
     * @post Poikkeustakuu: nothrow
     */
    QString title() const;

    /**
     * @brief location kertoo, minkä pelialueen pakkaan kortti kuuluu
     * @pre -
     * @return heikko osoitin pelialueelle, jonka pakkaan kortti kuuluu
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
     * @brief amount kertoo vaikutusvallan määrän
     * @pre -
     * @return palauttaa kortin vaikutusvallan
     * @post Poikkeustakuu: nothrow
     */
    unsigned short amount() const;

private:
    const QString name_;
    const std::weak_ptr<Location> location_;

    std::weak_ptr<Player> owner_;
    const unsigned short amount_;
};

} // Interface

#endif // INFLUENCE_H
