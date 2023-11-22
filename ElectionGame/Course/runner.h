#ifndef RUNNER_H
#define RUNNER_H

#include <QObject>

#include <map>
#include <memory>

/**
 * @file
 * @brief Pelaajien siirtoja kyselevä luokka
 */

namespace Interface
{

class ActionInterface;
class ControlInterface;
class Game;
class Player;

/**
 * @brief Runner kyselee pelaajien siirtoja ja suorittaa niitä.
 *
 * Käyttö tapahtuu seuraavasti:
 * 1. Aseta pelin pelaajille hallintaoliot.
 * 2. Kutsu run-metodia. Metodi alkaa kysellä siirtoja vuorossa olevien
 *    pelaajien hallintaolioilta ja suorittaa niitä. Kustakin suoritetusta
 *    siirrosta lähetetään actionPerformed-signaali.
 * 3. Jos run-kutsu palauttaa osoittimen hallintaolioon, on kyseessä vuorossa
 *    olevan pelaajan hallintaolio joka ei kyennyt antamaan seuraavaa siirtoa.
 *    Korjaa hallintaolion tila tai vaihda se uuteen, ja palaa kohtaan 2.
 * 4. Jos run-kutsu palauttaa null-osoittimen, peli on saatu päätökseen.
 *
 * Jos luokan metodi ei ole poikkeustakuultaan nothrow, voi metodista aina vuotaa ulos poikkeus `std::bad_alloc` (muisti loppui).
 */
class Runner: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Runner rakentaja
     * @pre game != nullptr
     * @param game peliolio
     * @post Runner luotu ja asetettu seuraamaan pelin staattista tilaa
     */
    explicit Runner(std::shared_ptr<Game> game);

    /**
     * @brief oletusarvoinen virtuaalipurkaja
     */
    virtual ~Runner() = default;

    /**
     * @brief playerControl palauttaa pelaajalle asetetun hallintaolion
     * @pre player != nullptr
     * @param player pelaaja
     * @return hallintaolio, tai tyhjä osoitin jos sellaista ei ole pelaajalle asetettu
     * @post Poikkeustakuu: nothrow
     */
    std::shared_ptr<ControlInterface> playerControl(std::shared_ptr<const Player> player) const;

    /**
     * @brief setPlayerControl asettaa pelaajalle hallintaolion
     * @pre player != nullptr
     * @param player pelaaja
     * @param control hallintaolio
     * @post pelaajalle on asetettu hallintaolio
     * @post Poikkeustakuu: vahva
     */
    void setPlayerControl(std::shared_ptr<const Player> player, std::shared_ptr<ControlInterface> control);

    /**
     * @brief run pyytää kulloinkin vuorossa olevan pelaajan hallintaoliolta siirtoja ja suorittaa niitä.
     * @pre -
     * @return hallintaolio, joka ei kyennyt antamaan seuraavaa siirtoa, tai tyhjä osoitin, jos peli on saatu päätökseen.
     * @post Kustakin suoritetusta siirrosta on signaloitu (signaali actionPerformed). Olio on valmis jatkamaan suoritusta.
     * @post Poikkeustakuu: perus (olio on heti valmis jatkamaan suoritusta)
     * @exception ControlException siirron tuottamisessa tapahtui virhe
     */
    std::shared_ptr<ControlInterface> run();

signals:
    /**
     * @brief actionPerformed lähetetään aina, kun siirto on suoritettu
     * @param player pelaaja, jonka siirto suoritettiin
     * @param action suoritettu siirto
     */
    void actionPerformed(std::shared_ptr<const Player> player, std::shared_ptr<ActionInterface> action) const;

private:
    std::shared_ptr<Game> game_;
    std::map<std::shared_ptr<const Player>, std::shared_ptr<ControlInterface> > playerControls_;
};

} // Interface

#endif // RUNNER_H
