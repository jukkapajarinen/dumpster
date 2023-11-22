#ifndef AGENT_H
#define AGENT_H

#include "agentinterface.h"
#include "location.h"
#include "player.h"
#include "stateexception.h"
#include <memory>

/**
 * @file
 * @brief Agenttikortit määrittävä luokka
 */

using Interface::AgentInterface;
using Interface::Location;
using Interface::Player;

/**
 * @brief Agent toteuttaa agenttikortit.
 * Agent on periytetty AgentInterface rajapinnasta, joka on periytetty
 * CardInterface rajapinnasta, joten se sisältää myös nekin.
 *
 * Luokan kaikki metodit ovat peritty em. rajapinnoista.
 */
class Agent : public AgentInterface {

public:
    /**
     * @brief Agent rakentaja
     * @pre -
     * @param name kortin nimi
     * @param placement pelilaudan alue, jonne kortti on pelattu
     * @param connections suhteiden määrä
     * @post Agenttikortilla on annettut nimi, alue, suhteiden määrä ja ei omistajaa.
     */
    explicit Agent(const QString &name, std::weak_ptr<Location> placement, int connections);

    /**
     * @brief oletusarvoinen virtuaalipurkaja
     */
    virtual ~Agent() = default;

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
    virtual QString name() const;

    /*!
     * @brief title palauttaa kortin arvonimen
     * @pre -
     * @return Kortin arvonimi merkkijonona
     * @post Poikkeustakuu: nothrow
     */
    virtual QString title() const;

    /**
     * @brief location kertoo, mihin pelialueeseen kortti liittyy
     * @pre -
     * @return heikko osoitin pelialueeseen johon kortti liittyy, tai tyhjä osoitin jos se ei liity mihinkään
     * @post Poikkeustakuu: nothrow
     */
    virtual std::weak_ptr<Location> location() const;

    /**
     * @brief owner kertoo pelaajan, joka omistaa kortin
     * @pre -
     * @return heikko osoitin kortin omistavaan pelaajaan, tai tyhjä osoitin jos sitä ei omista kukaan
     * @post Poikkeustakuu: nothrow
     */
    virtual std::weak_ptr<Player> owner() const;

    /**
     * @brief setOwner asettaa kortille omistajan
     * @pre -
     * @param owner heikko osoitin kortin omistajaan, tai tyhjä osoitin jos sitä ei omista kukaan
     * @post Kortilla on uusi omistaja
     * @post Poikkeustakuu: nothrow
     */
    virtual void setOwner(std::weak_ptr<Player> owner);

    /*!
     * @brief isCommon kertoo, onko kyseessä "geneerinen" agentti, joka ei liity mihinkään pelilaudan alueeseen
     * @pre -
     * @return tosi, joss agentti ei liity mihinkään pelilaudan alueeseen
     * @post Poikkeustakuu: nothrow
     */
    virtual bool isCommon() const;

    /**
     * @brief placement palauttaa tiedon agentin sijainnista
     * @pre -
     * @return heikko osoitin pelilaudan alueelle jossa agentti sijaitsee, tai tyhjä osoitin jos se ei ole laudalla
     * @post Poikkeustakuu: nothrow
     */
    virtual std::weak_ptr<Location> placement() const;

    /**
     * @brief setPlacement kertoo agentille millä pelialueella se on
     * @pre -
     * @param placement pelialue, tai tyhjä osoitin jos agentti ei ole laudalla
     * @post agentti tietää olevansa alueella
     * @post Poikkeustakuu: nothrow
     */
    virtual void setPlacement(std::weak_ptr<Location> placement);

    /**
     * @brief connections kertoo suhteiden tason
     * @pre -
     * @return palauttaa suhteiden senhetkisen tilanteen
     * @post Poikkeustakuu: nothrow
     */
    virtual unsigned short connections() const;

    /**
     * @brief setConnections asettaa agentille suhteiden tason
     * @pre -
     * @param connections uusi suhteiden taso
     * @post suhteet ovat parametrin mukaiset
     * @post Poikkeustakuu: vahva
     * @exception StateException jos rikkoisi invariantin
     */
    virtual void setConnections(unsigned short connections);

    /**
     * @brief setConnections muuttaa agentin suhteiden tasoa
     * @pre -
     * @param change suhteiden muutos
     * @post suhteita on muutettu parametrin mukaisesti
     * @post Poikkeustakuu: vahva
     * @exception StateException jos rikkoisi invariantin
     */
    virtual void modifyConnections(short amount);

private:
    const QString name_;
    std::weak_ptr<Location> location_;
    std::weak_ptr<Player> owner_;
    unsigned short connections_;
};

#endif // AGENT_H
