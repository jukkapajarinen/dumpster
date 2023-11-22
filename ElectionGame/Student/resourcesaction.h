#ifndef RESOURCESACTION_H
#define RESOURCESACTION_H

#include "actioninterface.h"
#include "agentinterface.h"
#include <memory>

/**
 * @file
 * @brief Resurssien keräämisen alueelta toteuttava luokka
 */

using Interface::ActionInterface;
using Interface::AgentInterface;
using Interface::Location;
using Interface::Player;

/**
 * @brief ResourcesAction toteuttaa resurssien keräämisen pelilaudan alueelta.
 * ResourcesAction on periytetty ActionInterface rajapinnasta, joten se sisältää myös sen.
 */
class ResourcesAction : public ActionInterface {

public:
    /**
     * @brief ResourcesAction rakentaja
     * @pre -
     * @param agent agenttikortti, jolla toiminto on pelattu
     * @param location pelilaudan alue, jonne kortti on pelattu
     * @param currentPlayer pelaaja, joka on pelannut toiminnon
     * @post ResourcesAction:illa on agenttikortti, pelilaudan alue ja pelaaja.
     */
    explicit ResourcesAction(std::shared_ptr<AgentInterface> agent,
                             std::shared_ptr<Location> location,
                             std::shared_ptr<Player> currentPlayer);

    /**
     * @brief canPerform tarkistaa, voiko agenttikortilla nostaa resurssin
     * @pre -
     * @return tosi, joss agentti on laudalla ja alueen pakasta voi nostaa kortin
     * @post Poikkeustakuu: nothrow
     */
    virtual bool canPerform() const;

    /**
     * @brief perform suorittaa resurssin noston alueelta
     * @pre -
     * @post alueen pakasta poistuu kortti ja se tulee pelaajan käteen.
     */
    virtual void perform();

private:
    std::shared_ptr<AgentInterface> agent_;
    std::shared_ptr<Location> location_;
    std::shared_ptr<Player> player_;
};

#endif // RESOURCESACTION_H
