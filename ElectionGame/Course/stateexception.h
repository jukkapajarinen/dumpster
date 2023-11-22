#ifndef STATEEXCEPTION_H
#define STATEEXCEPTION_H

#include "gameexception.h"

/**
  * @file
  * @brief Määrittelee olion käytön laittomassa tilassa ilmaisevan poikkeusluokan.
  */

namespace Interface
{

/**
 * @brief StateException on poikkeusluokka olion käytölle laittomassa tilassa.
 */
class StateException : public GameException
{
public:
    /**
     * @brief Rakentaja.
     * @param msg Poikkeuksen syytä selventävä viesti.
     * @pre -
     * @post Luo laittoman tilan StateException, joka sisältää poikkeuksen syytä selventävän viestin.
     */
    explicit StateException(const QString& msg = "");

    /**
     * @brief Purkaja.
     */
    virtual ~StateException() = default;
};

} // Interface

#endif // STATEEXCEPTION_H
