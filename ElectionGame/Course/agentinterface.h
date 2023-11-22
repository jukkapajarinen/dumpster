#ifndef AgentInterface_H
#define AgentInterface_H

#include "cardinterface.h"

/**
 * @file
 * @brief Määrittelee agenttikorttien rajapintaluokan.
 */

namespace Interface
{

/**
 * @brief AgentInterface määrittää rajapinnan agenttikorteille.
 *
 * AgentInterface on periytetty CardInterface-rajapinnasta eli sisältää myös senkin.
 *
 * Jos luokan metodi ei ole poikkeustakuultaan nothrow, voi metodista aina vuotaa ulos poikkeus `std::bad_alloc` (muisti loppui).
 *
 * @invariant jos (placement().lock() != nullptr) niin (connections() > 0) eli jos agentti pelilaudan alueella, sillä on suhteita
 */
class AgentInterface: public CardInterface
{
public:
    /**
     * @brief Rajapintaluokan oletusrakentaja (olemassa dokumentaatiota varten).
     * @post Agentti ei ole millään pelilaudan alueella ja sillä ei ole suhteita
     */
    AgentInterface() = default;

    /**
     * @brief Rajapintaluokassa on oletusarvoinen virtuaalipurkaja (olemassa, koska kantaluokalla tulee olla virtuaalipurkaja).
     */
    virtual ~AgentInterface() = default;

    /*!
     * @brief isCommon kertoo, onko kyseessä "geneerinen" agentti, joka ei liity mihinkään pelilaudan alueeseen
     * @pre -
     * @return tosi, joss agentti ei liity mihinkään pelilaudan alueeseen
     * @post Poikkeustakuu: nothrow
     */
    virtual bool isCommon() const = 0;

    /**
     * @brief placement palauttaa tiedon agentin sijainnista
     * @pre -
     * @return heikko osoitin pelilaudan alueelle jossa agentti sijaitsee, tai tyhjä osoitin jos se ei ole laudalla
     * @post Poikkeustakuu: nothrow
     */
    virtual std::weak_ptr<Location> placement() const = 0;

    /**
     * @brief setPlacement kertoo agentille millä pelialueella se on
     * @pre -
     * @param placement pelialue, tai tyhjä osoitin jos agentti ei ole laudalla
     * @post agentti tietää olevansa alueella
     * @post Poikkeustakuu: nothrow
     */
    virtual void setPlacement(std::weak_ptr<Location> placement) = 0;

    /**
     * @brief connections kertoo suhteiden tason
     * @pre -
     * @return palauttaa suhteiden senhetkisen tilanteen
     * @post Poikkeustakuu: nothrow
     */
    virtual unsigned short connections() const = 0;

    /**
     * @brief setConnections asettaa agentille suhteiden tason
     * @pre -
     * @param connections uusi suhteiden taso
     * @post suhteet ovat parametrin mukaiset
     * @post Poikkeustakuu: vahva
     * @exception StateException jos rikkoisi invariantin
     */
    virtual void setConnections(unsigned short connections) = 0;

    /**
     * @brief setConnections muuttaa agentin suhteiden tasoa
     * @pre -
     * @param change suhteiden muutos
     * @post suhteita on muutettu parametrin mukaisesti
     * @post Poikkeustakuu: vahva
     * @exception StateException jos rikkoisi invariantin
     */
    virtual void modifyConnections(short change) = 0;
};

} // Interface

#endif // AgentInterface_H
