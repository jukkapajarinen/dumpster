#ifndef ACTIONINTERFACE_H
#define ACTIONINTERFACE_H

/**
 * @file
 * @brief Määrittelee yksittäisen siirron kuvaavan rajapintaluokan
 */

namespace Interface
{

/**
 * @brief ActionInterface on rajapinta yksittäiselle pelin siirrolle.
 *
 * Jos luokan metodi ei ole poikkeustakuultaan nothrow, voi metodista aina vuotaa ulos poikkeus `std::bad_alloc` (muisti loppui).
 */
class ActionInterface
{
public:
    /**
     * @brief Rajapintaluokan oletusrakentaja (olemassa dokumentaatiota varten).
     */
    ActionInterface() = default;

    /**
     * @brief Rajapintaluokassa on oletusarvoinen virtuaalipurkaja (olemassa, koska kantaluokalla tulee olla virtuaalipurkaja).
     */
    virtual ~ActionInterface() = default;

    /**
     * @brief canPerform kertoo, onko siirto tehtävissä
     * @pre -
     * @return tosi, joss siirto on tehtävissä
     * @post Poikkeustakuu: nothrow
     */
    virtual bool canPerform() const = 0;

    /**
     * @brief perform suorittaa siirron
     * @pre siirto on tehtävissä
     * @post Poikkeustakuu: nothrow
     */
    virtual void perform() = 0;
};

} // Interface

#endif // ACTIONINTERFACE_H
