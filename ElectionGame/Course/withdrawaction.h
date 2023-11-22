#ifndef WITHDRAWACTION_H
#define WITHDRAWACTION_H

#include "actioninterface.h"

#include <memory>

/**
 * @file
 * @brief Agentin vetäytymisen laudalta toteuttava luokka
 */

namespace Interface
{

class AgentInterface;

/**
 * @brief WithdrawAction toteuttaa agentin vetäytymisen laudan alueelta.
 *
 * Jos luokan metodi ei ole poikkeustakuultaan nothrow, voi metodista aina vuotaa ulos poikkeus `std::bad_alloc` (muisti loppui).
 */
class WithdrawAction: public ActionInterface
{
public:

    /**
     * @brief Rakentaja
     * @param agent jaettu osoitin agenttikorttiin
     * @pre -
     * @post Vetäytyminen alueelta agentille luotu
     */
    explicit WithdrawAction(std::shared_ptr<AgentInterface> agent);

    /**
     * @brief oletusarvoinen virtuaalipurkaja
     */
    virtual ~WithdrawAction() = default;

    /**
     * @brief canPerform tarkistaa, voiko agentti vetäytyä laudan alueelta
     * @pre -
     * @return tosi, joss agentti on laudalla
     * @post Poikkeustakuu: nothrow
     */
    virtual bool canPerform() const;

    /**
     * @brief perform suorittaa agentin vetäytymisen laudan alueelta
     * @pre -
     * @post agentti vetäytyy alueelta, agenttikortti palaa omistajansa käteen.
     * @post Poikkeustakuu: vahva
     */
    virtual void perform();

private:
    std::shared_ptr<AgentInterface> agent_;
};

} // Interface

#endif // WITHDRAWACTION_H
