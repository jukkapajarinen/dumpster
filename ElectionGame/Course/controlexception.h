#ifndef CONTROLEXCEPTION_H
#define CONTROLEXCEPTION_H

#include "gameexception.h"

/**
  * @file
  * @brief Määrittelee hallintaoliossa tapahtuvia virheitä ilmaisevan poikkeusluokan.
  */

namespace Interface
{

/**
 * @brief ControlException on poikkeusluokka hallintaolion toiminnan virheille.
 */
class ControlException: public GameException
{
public:
    /**
     * @brief Rakentaja.
     * @param msg Poikkeuksen syytä selventävä viesti.
     * @pre -
     * @post Luo hallintavirheen ControlException, joka sisältää poikkeuksen syytä selventävän viestin.
     */
    explicit ControlException(const QString& msg = "");

    /**
     * @brief Purkaja.
     */
    virtual ~ControlException() = default;
};

} // Interface

#endif // CONTROLEXCEPTION_H
