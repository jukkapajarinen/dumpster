#ifndef MANUALCONTROL_H
#define MANUALCONTROL_H

#include "controlinterface.h"

/**
 * @file
 * @brief Käyttöliittymän kautta peliä pelaavaa ihmistä kuvaava luokka
 */

namespace Interface
{

/**
 * @brief ManualControl kuvaa käyttöliittymän kautta pelia pelaavaa ihmistä. Perii ControlInterface eli sisältää myös sen.
 *
 * Tämä luokka on tarkoitettu kuvaamaan ihmispelaajaa, eikä osaa itsessään
 * tuottaa siirtoja. Sen sijaan sille voi ulkoa päin (käyttöliittymästä
 * käskien) asettaa siirron, jonka se sitten palauttaa seuraavaksi.
 *
 * Jos luokan metodi ei ole poikkeustakuultaan nothrow, voi metodista aina vuotaa ulos poikkeus `std::bad_alloc` (muisti loppui).
 */
class ManualControl: public ControlInterface
{
public:
    /**
     * @brief oletusrakentaja
     * @post hallintaolio ilman seuraavaa siirtoa
     */
    explicit ManualControl();

    /**
     * @brief oletusarvoinen virtuaalipurkaja
     */
    virtual ~ManualControl() = default;

    /**
     * @brief nextAction palauttaa seuraavan siirron
     * @pre -
     * @return jaettu osoitin seuraavaan siirtoon, tai tyhjä osoitin jos sitä ei ole asetettu
     * @post seuraavaa siirtoa ei ole asetettu
     * @post Poikkeustakuu: nothrow
     */
    virtual std::shared_ptr<ActionInterface> nextAction();

    /**
     * @brief setNextAction asettaa seuraavan siirron
     * @pre -
     * @param action seuraava siirto
     * @post seuraava siirto on asetettu parametrin mukaiseksi
     * @post Poikkeustakuu: nothrow
     */
    void setNextAction(std::shared_ptr<ActionInterface> action);

private:
    std::shared_ptr<ActionInterface> action_;
};

} // Interface

#endif // MANUALCONTROL_H
