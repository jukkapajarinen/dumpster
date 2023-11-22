#ifndef IOEXCEPTION_H
#define IOEXCEPTION_H

#include "gameexception.h"
/**
  * @file
  * @brief Määrittelee tiedostojen käsittelyssä tapahtuvia virheitä ilmaisevan poikkeusluokan.
  */

namespace Interface
{

/**
 * @brief IoException on poikkeusluokka tiedostonkäsittelyn virheille.
 */
class IoException : public GameException
{
public:
    /**
     * @brief Rakentaja.
     * @param msg Poikkeuksen syytä selventävä viesti.
     * @pre -
     * @post Luo tiedostovirheen IOException, joka sisältää poikkeuksen syytä selventävän viestin.
     */
    explicit IoException(const QString& msg = "");

    /**
     * @brief Purkaja.
     */
    virtual ~IoException() = default;
};

} // Interface

#endif // IOEXCEPTION_H
