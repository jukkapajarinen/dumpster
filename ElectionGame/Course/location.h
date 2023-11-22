#ifndef LOCATION_H
#define LOCATION_H

#include <QObject>
#include <QString>

#include <map>
#include <memory>
#include <set>

/**
 * @file
 * @brief pelilaudan alueen kortteineen ja pelimerkkeineen kuvaava luokka
 */

namespace Interface
{

class AgentInterface;
class Councilor;
class DeckInterface;
class Player;

/**
 * @brief Location kuvaa pelilaudan alueen kortteineen ja pelimerkkeineen.
 *
 * Luokan kaikilla metodeilla on esiehtona, että olio on jaettujen osoittimien
 * omistuksessa.
 *
 * Luokan kaikilla metodeilla (paitsi initialize()) on esiehtona, että
 * initialize()-metodia on kutsuttu.
 *
 * Jos luokan metodi ei ole poikkeustakuultaan nothrow, voi metodista aina vuotaa ulos poikkeus `std::bad_alloc` (muisti loppui).
 */
class Location: public QObject, public std::enable_shared_from_this<Location>
{
    Q_OBJECT
public:
    /**
     * @brief Location rakentaja
     * @pre id ei ole ennestään tunnisteena yhdelläkään alueella
     * @param id tunniste alueelle
     * @param name alueen nimi
     * @post alueella on annetut tunniste ja nimi, tyhjät peli- ja hylkypakka, ja ei agentteja, neuvosta tai vaikutusvaltaa
     */
    explicit Location(unsigned short id, const QString& name);

    /**
     * @brief virtuaalipurkaja
     */
    virtual ~Location() = default;

    /**
     * @brief initialize suorittaa rakentajan jälkeiset alustustoimenpiteet
     * @pre metodia ei ole kutsuttu aikaisemmin
     * @post oliolle voi kutsua muita metodeita
     * @post Poikkeustakuu: perus
     */
    virtual void initialize();

    /**
     * @brief id palauttaa alueen tunnisteen
     * @pre -
     * @return alueen tunniste
     * @post Poikkeustakuu: nothrow
     */
    unsigned short id() const;

    /**
     * @brief name palauttaa alueen nimen
     * @pre -
     * @return alueen nimi
     * @post Poikkeustakuu: nothrow
     */
    QString name() const;

    /**
     * @copydoc deck()
     */
    std::shared_ptr<const DeckInterface> deck() const;
    /**
     * @brief deck palauttaa alueen pelipakan
     * @pre -
     * @return alueen pelipakka
     * @post Poikkeustakuu: nothrow
     */
    std::shared_ptr<DeckInterface> deck();

    /**
     * @copydoc discards()
     */
    std::shared_ptr<const DeckInterface> discards() const;
    /**
     * @brief discards palauttaa alueen hylkypakan
     * @pre -
     * @return alueen hylkypakka
     * @post Poikkeustakuu: nothrow
     */
    std::shared_ptr<DeckInterface> discards();

    /**
     * @copydoc agents()
     */
    std::set<std::shared_ptr<const AgentInterface> > agents() const;
    /**
     * @brief agents palauttaa alueelle pelatut agentit
     * @pre -
     * @return alueen agentit
     * @post Poikkeustakuu: vahva
     */
    std::set<std::shared_ptr<AgentInterface> > agents();

    /**
     * @brief canSendAgent kertoo, voiko pelaaja pelata agentin alueelle
     * @pre owner != nullptr
     * @param owner pelattavan agentin omistaja
     * @return tosi, joss pelaajalla ei ole ennestään agenttia alueella
     * @post Poikkeustakuu: nothrow
     */
    virtual bool canSendAgent(std::shared_ptr<const Player> owner) const;

    /**
     * @brief sendAgent lisää agentin alueelle
     * @pre agent != nullptr; agentin omistaja voi pelata agentin alueelle; agentti ei ole laudalla, missään pakassa tai kenenkään pelaajan kädessä
     * @param agent lisättävä agentti
     * @post Agentti on alueella ja tietää olevansa siellä. Agenttien muutoksesta on signaloitu (signaali agentsChanged).
     */
    virtual void sendAgent(std::shared_ptr<AgentInterface> agent);

    /**
     * @brief removeAgent poistaa agentin alueelta
     * @pre agentti on tällä alueella
     * @param agent poistettava agentti
     * @post Agentti ei ole alueella ja tietää ettei ole siellä. Agenttien muutoksesta on signaloitu (signaali agentsChanged).
     */
    virtual void removeAgent(std::shared_ptr<AgentInterface> agent);

    /**
     * @copydoc councilor()
     */
    std::shared_ptr<const Councilor> councilor() const;
    /**
     * @brief councilor kertoo alueen neuvoksen
     * @pre -
     * @return alueen neuvos
     * @post Poikkeustakuu: nothrow
     */
    std::shared_ptr<Councilor> councilor();

    /**
     * @brief setCouncilor asettaa alueelle neuvoksen
     * @pre -
     * @param councilor uusi neuvos, tai tyhjä osoitin jos alue halutaan jättää ilman neuvosta
     * @post neuvos on asetettu alueelle
     * @post Poikkeustakuu: nothrow
     */
    void setCouncilor(std::shared_ptr<Councilor> councilor);

    /**
     * @brief influence kertoo pelaajan vaikutusvallan alueen neuvokseen
     * @pre player != nullptr
     * @param player pelaaja
     * @return pelaajan vaikutusvalta
     * @post Poikkeustakuu: nothrow
     */
    unsigned short influence(std::shared_ptr<const Player> player) const;

    /**
     * @brief setInfluence asettaa pelaajan vaikutusvallan alueen neuvokseen
     * @pre player != nullptr
     * @param player pelaaja
     * @param influence uusi vaikutusvalta
     * @post Uusi vaikutusvalta on asetettu. Vaikutusvallan muutoksesta on signaloitu (signaali influenceChanged).
     * @post Poikkeustakuu: vahva
     */
    void setInfluence(std::shared_ptr<const Player> player, unsigned short influence);

signals:
    /**
     * @brief agentsChanged lähetetään, kun alueen agenttien tilassa tapahtuu muutos
     * @param location tämä alue
     */
    void agentsChanged(std::shared_ptr<const Location> location) const;

    /**
     * @brief influenceChanged lähetetään, kun jonkun pelaajan vaikutusvalta alueen neuvokseen muuttuu
     * @param location tämä alue
     */
    void influenceChanged(std::shared_ptr<const Location> location) const;

    /**
     * @brief deckChanged lähetetään, kun alueen pelipakan tila muuttuu
     * @param location tämä alue
     */
    void deckChanged(std::shared_ptr<const Location> location) const;

    /**
     * @brief discardsChanged lähetetään, kun alueen hylkypakan tila muuttuu
     * @param location tämä alue
     */
    void discardsChanged(std::shared_ptr<const Location> location) const;

private:
    const unsigned short id_;
    const QString name_;

    std::shared_ptr<DeckInterface> deck_;
    std::shared_ptr<DeckInterface> discards_;

    std::set<std::shared_ptr<AgentInterface> > agents_;

    std::shared_ptr<Councilor> councilor_;

    std::map<unsigned short, unsigned short> influence_;

private slots:
    void updateAgents();
    void updateDeck();
    void updateDiscards();
};

} // Interface

#endif // LOCATION_H
