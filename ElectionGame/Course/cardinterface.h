#ifndef CARD_H
#define CARD_H

#include <QString>

#include <memory>

/**
 * @file
 * @brief Määrittelee pelissä käytettäville korteille rajapintaluokan.
 */

namespace Interface
{

class Location;
class Player;

/**
 * @brief CardInterface määrittelee rajapinnan pelissä käytettäville korteille.
 *
 * Jos luokan metodi ei ole poikkeustakuultaan nothrow, voi metodista aina vuotaa ulos poikkeus `std::bad_alloc` (muisti loppui).
 */
class CardInterface
{
public:
    /**
     * @brief Rajapintaluokan oletusrakentaja (olemassa dokumentaatiota varten).
     * @post kortti ei ole kenenkään pelaajan omistuksessa
     */
    CardInterface() = default;

    /**
     * @brief Rajapintaluokassa on oletusarvoinen virtuaalipurkaja (olemassa, koska kantaluokalla tulee olla virtuaalipurkaja).
     */
    virtual ~CardInterface() = default;

    /**
     * @brief typeName palauttaa kortin tyypin
     * @pre -
     * @return Kortin tyyppi merkkijonona
     * @post Poikkeustakuu: nothrow
     */
    virtual QString typeName() const = 0;

    /*!
     * @brief name palauttaa kortin nimen
     * @pre -
     * @return Kortin nimi merkkijonona
     * @post Poikkeustakuu: nothrow
     */
    virtual QString name() const = 0;

    /*!
     * @brief title palauttaa kortin arvonimen
     * @pre -
     * @return Kortin arvonimi merkkijonona
     * @post Poikkeustakuu: nothrow
     */
    virtual QString title() const = 0;

    /**
     * @brief location kertoo, mihin pelialueeseen kortti liittyy
     * @pre -
     * @return heikko osoitin pelialueeseen johon kortti liittyy, tai tyhjä osoitin jos se ei liity mihinkään
     * @post Poikkeustakuu: nothrow
     */
    virtual std::weak_ptr<Location> location() const = 0;

    /**
     * @brief owner kertoo pelaajan, joka omistaa kortin
     * @pre -
     * @return heikko osoitin kortin omistavaan pelaajaan, tai tyhjä osoitin jos sitä ei omista kukaan
     * @post Poikkeustakuu: nothrow
     */
    virtual std::weak_ptr<Player> owner() const = 0;

    /**
     * @brief setOwner asettaa kortille omistajan
     * @pre -
     * @param owner heikko osoitin kortin omistajaan, tai tyhjä osoitin jos sitä ei omista kukaan
     * @post Kortilla on uusi omistaja
     * @post Poikkeustakuu: nothrow
     */
    virtual void setOwner(std::weak_ptr<Player> owner) = 0;
};

} // Interface

#endif // CARD_H
