#ifndef RANGEEXCEPTION_H
#define RANGEEXCEPTION_H

#include "gameexception.h"

/**
  * @file
  * @brief Määrittelee yli-indekstointivirheitä ilmaisevan poikkeusluokan.
  */

namespace Interface
{

/**
 * @brief RangeException on poikkeusluokka yli-indeksoinnille.
 */
class RangeException : public GameException
{
public:
    /**
     * @brief Rakentaja.
     * @param msg Poikkeuksen syytä selventävä viesti.
     * @pre -
     * @post Luo yli-indekstointivirheen RangeException, joka sisältää poikkeuksen syytä selventävän viestin.
     */
    explicit RangeException(const QString& msg = "");

    /**
     * @brief Purkaja.
     */
    virtual ~RangeException() = default;
};

} // Interface

#endif // RANGEEXCEPTION_H
