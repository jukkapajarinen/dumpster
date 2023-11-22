#ifndef GAMEEXCEPTION_H
#define GAMEEXCEPTION_H

#include <QString>

/**
  * @file
  * @brief Määrittelee pelissä tapahtuvia virheitä ilmaisevan poikkeusluokan.
  */

namespace Interface
{

/**
 * @brief GameException on kantaluokka pelissä käytettäville poikkeuksille.
 */
class GameException
{
public:
    /**
     * @brief Rakentaja.
     * @param msg Poikkeuksen syytä selventävä viesti.
     * @pre -
     * @post Luo pelivirheen, joka sisältää poikkeuksen syytä selventävän viestin.
     */
    explicit GameException(const QString& msg = "");

    /**
     * @brief Purkaja.
     */
    virtual ~GameException() = default;

    /**
     * @brief msg antaa poikkeuksen syytä selventävän viestin.
     * @pre -
     * @post Poikkeustakuu: nothrow.
     * @return Rakentajassa annettu viesti tai tyhjä merkkijono.
     */
    virtual QString msg() const;

private:
    const QString msg_;
};

} // Interface

#endif // GAMEEXCEPTION_H
