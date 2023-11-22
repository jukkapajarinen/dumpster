#ifndef FORMATEXCEPTION_H
#define FORMATEXCEPTION_H

#include "gameexception.h"

/**
  * @file
  * @brief Määrittelee datan rakenteessa tapahtuvia virheitä ilmaisevan poikkeusluokan.
  */

namespace Interface
{

/**
 * @brief FormatException on poikkeusluokka virheelliselle datan rakenteelle.
 */
class FormatException : public GameException
{
public:
    /**
     * @brief Rakentaja.
     * @param msg Poikkeuksen syytä selventävä viesti.
     * @pre -
     * @post Luo rakennevirheen FormatException, joka sisältää poikkeuksen syytä selventävän viestin.
     */
    explicit FormatException(const QString& msg = "");

    /**
     * @brief Purkaja.
     */
    virtual ~FormatException() = default;
};

} // Interface

#endif // FORMATEXCEPTION_H
