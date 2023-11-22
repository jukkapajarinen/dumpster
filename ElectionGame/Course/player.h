#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

#include <memory>
#include <vector>

/**
 * @file
 * @brief Yksittäisen pelaajan kuvaava luokka
 */

namespace Interface
{

class CardInterface;
class Councilor;
class Game;

/**
 * @brief Player kuvaa yksittäisen pelaajan.
 *
 * Luokka kuvaa pelaajan osana pelin tilaa, ikään kuin pelaajan avatarin sikäli
 * kuin termiä voi lautapelissä käyttää. Sen ei ole tarkoitus kuvata pelaajaa
 * tahona, joka tekee päätöksiä.
 *
 * Luokan kaikilla metodeilla on esiehtona, että olio on jaettujen osoittimien
 * omistuksessa.
 *
 * Jos luokan metodi ei ole poikkeustakuultaan nothrow, voi metodista aina vuotaa ulos poikkeus `std::bad_alloc` (muisti loppui).
 */
class Player: public std::enable_shared_from_this<Player>
{
public:
    /**
     * @brief Player rakentaja
     * @pre game.lock() != nullptr; id ei ole ennestään tunnisteena yhdelläkään pelaajalla
     * @param game peliolio
     * @param id tunniste pelaajalle
     * @param name pelaajan nimi
     * @post pelaajalla on annetut tunniste ja nimi, ja ei neuvosta tai kortteja kädessä
     */
    explicit Player(std::weak_ptr<Interface::Game> game, unsigned short id, const QString& name);

    /**
     * @brief oletusarvoinen virtuaalipurkaja
     */
    virtual ~Player() = default;

    /**
     * @brief id palauttaa alueen tunnisteen
     * @pre -
     * @return alueen tunniste
     * @post Poikkeustakuu: nothrow
     */
    virtual unsigned short id() const;

    /**
     * @brief name palauttaa pelaajan nimen
     * @pre -
     * @return pelaajan nimi
     * @post Poikkeustakuu: nothrow
     */
    virtual QString name() const;

    /**
     * @copydoc councilor()
     */
    virtual std::shared_ptr<const Interface::Councilor> councilor() const;
    /**
     * @brief councilor palauttaa neuvoston jäsenen (kortin), jonka roolissa pelaaja on
     * @pre -
     * @return pelaajan neuvoskortti, tai tyhjä osoitin jos sellaista ei ole asetettu
     * @post Poikkeustakuu: nothrow
     */
    virtual std::shared_ptr<Interface::Councilor> councilor();

    /**
     * @brief setCouncilor asettaa neuvoston jäsenen (kortin), jonka roolissa pelaaja on
     * @pre -
     * @param councilor pelaajan neuvoskortti
     * @post pelaajalle on asetettu neuvos rooliksi
     * @post Poikkeustakuu: nothrow
     */
    virtual void setCouncilor(std::shared_ptr<Interface::Councilor> councilor);

    /**
     * @copydoc cards()
     */
    virtual std::vector<std::shared_ptr<const Interface::CardInterface> > cards() const;
    /**
     * @brief cards palauttaa pelaajan kädessä olevat kortit
     * @pre -
     * @return pelaajan kädessä olevat kortit
     * @post Poikkeustakuu: vahva
     */
    virtual std::vector<std::shared_ptr<Interface::CardInterface> > cards();

    /**
     * @brief addCard lisää kortin pelaajan käteen
     * @pre card != nullptr; kortti ei ole laudalla, missään pakassa tai kenenkään pelaajan kädessä
     * @param card lisättävä kortti
     * @post kortti on lisätty pelaajan käteen
     * @post Poikkeustakuu: vahva
     */
    virtual void addCard(std::shared_ptr<Interface::CardInterface> card);

    /**
     * @brief playCard ottaa kortin pelaajan kädestä pelattavaksi
     * @pre kortti on pelaajan kädessä
     * @param card kortti
     * @post kortti on poistettu pelaajan kädestä
     * @post Poikkeustakuu: nothrow
     */
    virtual void playCard(std::shared_ptr<const Interface::CardInterface> card);

private:
    const std::weak_ptr<Interface::Game> game_;

    const unsigned short id_;
    const QString name_;

    std::shared_ptr<Interface::Councilor> councilor_;
    std::vector<std::shared_ptr<Interface::CardInterface> > cards_;
};

} // Interface

#endif // PLAYER_H
