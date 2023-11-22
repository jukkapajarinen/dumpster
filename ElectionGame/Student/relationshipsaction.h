#ifndef RELATIONSHIPSACTION_H
#define RELATIONSHIPSACTION_H

#include "actioninterface.h"
#include "agentinterface.h"
#include <limits.h>
#include <memory>

/**
 * @file
 * @brief Suhteiden vaalimisen alueella toteuttava luokka
 */

using Interface::ActionInterface;
using Interface::AgentInterface;

/**
 * @brief RelationshipsAction toteuttaa suhteiden vaalimisen pelilaudan alueella.
 * RelationshipsAction on periytetty ActionInterface rajapinnasta, joten se sisältää myös sen.
 */
class RelationshipsAction : public ActionInterface {

public:
    /**
     * @brief RelationshipsAction rakentaja
     * @pre -
     * @param agent agenttikortti, jolla toiminto on pelattu
     * @post RelationshipsAction:illa on agenttikortti.
     */
    explicit RelationshipsAction(std::shared_ptr<AgentInterface> agent);

    /**
     * @brief canPerform tarkistaa, voiko agenttikortilla vaalia suhteita
     * @pre -
     * @return tosi, joss agentti on laudalla ja suhteiden määrä on sen arvoalueen sisällä.
     * @post Poikkeustakuu: nothrow
     */
    virtual bool canPerform() const;

    /**
     * @brief perform suorittaa suhteiden vaalimisen alueella
     * @pre -
     * @post alueelle pelatun agenttikortin suhteet alueeseen kasvaa yhdellä
     */
    virtual void perform();

private:
    std::shared_ptr<AgentInterface> agent_;
};

#endif // RELATIONSHIPSACTION_H
