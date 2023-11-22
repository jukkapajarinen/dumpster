#ifndef DECKINTERFACE_H
#define DECKINTERFACE_H

#include <memory>

/**
 * @file
 * @brief rajapintaluokka korttipakkojen määrittelemistä varten
 */

namespace Interface
{

class CardInterface;

/**
 * @brief DeckInterface on rajapinta korttipakkoja kuvaaville luokille.
 *
 * Jos luokan metodi ei ole poikkeustakuultaan nothrow, voi metodista aina vuotaa ulos poikkeus `std::bad_alloc` (muisti loppui).
 */
class DeckInterface
{
public:
    /**
     * @brief Rajapintaluokan oletusrakentaja (olemassa dokumentaatiota varten).
     * @post Pakka on tyhjä
     */
    DeckInterface() = default;

    /**
     * @brief Rajapintaluokassa on oletusarvoinen virtuaalipurkaja (olemassa, koska kantaluokalla tulee olla virtuaalipurkaja).
     */
    virtual ~DeckInterface() = default;

    /**
     * @brief size palauttaa pakan koon
     * @pre -
     * @return korttipakan koko
     * @post Poikkeustakuu: nothrow
     */
    virtual unsigned int size() const = 0;

    /**
     * @copydoc cardAt(unsigned int i)
     */
    virtual std::shared_ptr<const CardInterface> cardAt(unsigned int i) const = 0;
    /**
     * @brief cardAt palauttaa kortin pakasta
     * @pre i pakan koon sisällä
     * @param i kortin sijainti pakassa, 0 on pohjimmainen
     * @return jaettu osoitin korttiin sijainnissa i
     * @post Poikkeustakuu: vahva
     */
    virtual std::shared_ptr<CardInterface> cardAt(unsigned int i) = 0;

    /**
     * @brief canDraw tarkistaa, voiko pakasta nostaa korttia
     * @pre -
     * @return tosi, joss pakassa on vähintään yksi kortti
     * @post Poikkeustakuu: nothrow
     */
    virtual bool canDraw() const = 0;

    /**
     * @brief visible kertoo ovatko kortit pakassa kuvapuoli ylöspäin
     * @pre -
     * @return tosi, joss kortit ovat pakassa kuvapuoli ylöspäin
     * @post Poikkeustakuu: nothrow
     */
    virtual bool visible() const = 0;

    /**
     * @brief addCard lisää kortin pakkaan
     * @pre card != nullptr; kortti ei ole laudalla, missään pakassa tai kenenkään pelaajan kädessä
     * @param card lisättävä kortti
     * @param toBottom tieto siitä, lisätäänkö kortti pakan pohjalle. Oletuksena kortti lisätään päälle.
     * @post kortti card on lisätty pakkaan parametrin mukaiseen paikkaan
     * @post Poikkeustakuu: vahva
     */
    virtual void addCard(std::shared_ptr<CardInterface> card, bool toBottom = false) = 0;

    /**
     * @brief draw nostaa kortin pakasta
     * @pre pakasta voi nostaa kortin
     * @return palauttaa nostetun kortin
     * @post kortti poistettu pakasta
     * @post Poikkeustakuu: nothrow
     */
    virtual std::shared_ptr<CardInterface> draw() = 0;

    /**
     * @copydoc peek()
     */
    virtual std::shared_ptr<const CardInterface> peek() const = 0;
    /**
     * @brief peek kurkistaa pakan päälimmäistä korttia
     * @pre pakassa on vähintään yksi kortti
     * @return palauttaa jaetun osoittimen pakan päällimmäiseen korttiin
     * @post Poikkeustakuu: nothrow
     */
    virtual std::shared_ptr<CardInterface> peek() = 0;

    /**
     * @brief shuffle sekoittaa pakan
     * @pre -
     * @post pakan kortit ovat satunnaisessa järjestyksessä
     * @post Poikkeustakuu: perus
     */
    virtual void shuffle() = 0;
};

} // Interface

#endif // DECKINTERFACE_H
