#ifndef CONTROLINTERFACE_H
#define CONTROLINTERFACE_H

#include <memory>

/**
 * @file
 * @brief Siirtoja tekevän tahon määrittelevä rajapintaluokka
 */

namespace Interface
{

class ActionInterface;

/**
 * @brief ControlInterface määrittää rajapinnan siirtoja tekevälle taholle.
 *
 * Rajapinta kuvaa pelin siirtoja tuottavia tahoja, kuten käyttöliittymän
 * kautta pelaavaa ihmistä, tekoälyä, tai etäyhteyden päässä olevaa pelaajaa.
 *
 * Jos luokan metodi ei ole poikkeustakuultaan nothrow, voi metodista aina vuotaa ulos poikkeus `std::bad_alloc` (muisti loppui).
 */
class ControlInterface
{
public:
    /**
     * @brief Rajapintaluokan oletusrakentaja (olemassa dokumentaatiota varten).
     */
    ControlInterface() = default;

    /**
     * @brief Rajapintaluokassa on oletusarvoinen virtuaalipurkaja (olemassa, koska kantaluokalla tulee olla virtuaalipurkaja).
     */
    virtual ~ControlInterface() = default;

    /**
     * @brief nextAction kertoo seuraavan suoritettavan siirron
     * @pre -
     * @return jaettu osoitin seuraavaan siirtoon, tai tyhjä osoitin jos siirtoa ei voi tuottaa
     * @post Poikkeustakuu: minimi
     * @exception ControlException seuraavan siirron määrittämisessä tapahtui virhe
     */
    virtual std::shared_ptr<ActionInterface> nextAction() = 0;
};

} // Interface

#endif // CONTROLINTERFACE_H
