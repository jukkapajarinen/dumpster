#ifndef KEYEXCEPTION_H
#define KEYEXCEPTION_H

#include "gameexception.h"
/**
  * @file
  * @brief Määrittelee tuntemattoman hakuavaimen käytössä tapahtuvia virheitä ilmaisevan poikkeusluokan.
  */
namespace Interface
{

/**
 * @brief KeyException on poikkeusluokka tuntemattoman hakuavaimen käytölle.
 */
class KeyException : public GameException
{
public:
     /**
      * @brief Rakentaja.
      * @param msg Poikkeuksen syytä selventävä viesti.
      * @pre -
      * @post Luo tuntemattoman hakuavainvirheen KeyException, joka sisältää poikkeuksen syytä selventävän viestin.
      */
    explicit KeyException(const QString& msg = "");

    /**
     * @brief Purkaja.
     */
    virtual ~KeyException() = default;
};

} // Interface

#endif // KEYEXCEPTION_H
