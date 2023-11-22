#ifndef NEGOTIATIONACTION_H
#define NEGOTIATIONACTION_H

#include "actioninterface.h"
#include "agentinterface.h"
#include "location.h"
#include <memory>

/**
 * @file
 * @brief Neuvottelun pitämisen alueella toteuttava luokka
 */

using Interface::ActionInterface;
using Interface::AgentInterface;

/**
 * @brief NegotiationAction toteuttaa neuvottelun pitämisen pelilaudan alueella.
 * NegotiationAction on periytetty ActionInterface rajapinnasta, joten se sisältää myös sen.
 */
class NegotiationAction : public ActionInterface {

public:
    /**
     * @brief NegotiationAction rakentaja
     * @pre -
     * @param agent agenttikortti, jolla toiminto on pelattu
     * @post NegotiationAction:illa on agenttikortti
     */
    explicit NegotiationAction(std::shared_ptr<AgentInterface> agent);

    /**
     * @brief canPerform tarkistaa, voiko agenttikortilla neuvotella
     * @pre -
     * @return tosi, joss agentti on laudalla ja vaikutusvallan määrä alueella on sen arvoalueen sisällä.
     * @post Poikkeustakuu: nothrow
     */
    virtual bool canPerform() const;

    /**
     * @brief perform suorittaa neuvottelun pitämisen alueella
     * @pre -
     * @post pelaajan vaikutusvalta alueella kasvaa yhdellä
     */
    virtual void perform();

private:
    std::shared_ptr<AgentInterface> agent_;
};

#endif // NEGOTIATIONACTION_H
