#include "agent.h"
#include "location.h"
#include "player.h"
#include "game.h"
#include "stateexception.h"
#include <QSignalSpy>
#include <QtTest>
#include <memory>

using Interface::AgentInterface;
using Interface::Location;
using Interface::Player;
using Interface::Game;
using Interface::StateException;

class TestAgent : public QObject {
    Q_OBJECT

public:
    TestAgent();

private Q_SLOTS:
    void testConstructor();
    void testTypeName();
    void testName();
    void testTitle();
    void testLocation();
    void testOwner();
    void testSetOwner();
    void testIsCommon();
    void testPlacement();
    void testSetPlacement();
    void testConnections();
    void testSetConnections();
    void testModifyConnections();
};

TestAgent::TestAgent() {}

/**
 * @brief TestAgent::testConstructor
 *
 * Testaa Agentin Agent(const QString &name,
 * std::weak_ptr<Interface::Location> placement,
 * int connections) rakentajan.
 *
 * Luodaan luokasta olio käyttäen rakentajaa ja sen parametrejä.
 * Varmistetaan, että parametrit päätyvät oliolle.
 */
void TestAgent::testConstructor() {
    QString name = QString("Agentti");
    std::shared_ptr<Location> placement = std::make_shared<Location>(0, "Kuninkaanlinna");
    int connections = 5;
    std::shared_ptr<Agent> agent = std::make_shared<Agent>(name, placement, connections);
    QVERIFY2(agent->name() == name, "Virhe, name on väärin");
    QVERIFY2(agent->placement().lock() == placement, "Virhe, placement on väärin");
    QVERIFY2(agent->connections() == connections, "Virhe, connections on väärin");
}

/**
 * @brief TestAgent::testTypeName
 *
 * Testaa CardInterfacesta perityn typeName() funktion.
 *
 * Luodaan luokasta olio, jonka typeName pitäisi olla aina "Agent".
 * Varmistetaan, että kortin typeName palauttaa oikean arvon.
 */
void TestAgent::testTypeName() {
    QString name = QString("Agentti");
    std::shared_ptr<Location> placement = std::make_shared<Location>(0, "Kuninkaanlinna");
    int connections = 5;
    std::shared_ptr<Agent> agent = std::make_shared<Agent>(name, placement, connections);
    QVERIFY2(agent->typeName() == QString("Agent"), "Virhe, typeName on väärin");
}

/**
 * @brief TestAgent::testName
 *
 * Testaa CardInterfacesta perityn name() funktion.
 *
 * Luodaan luokasta olio ja annetaan sille nimi rakentajassa.
 * Varmistetaan, että kortin name palauttaa oikean arvon.
 */
void TestAgent::testName() {
    QString name = QString("Agentti");
    std::shared_ptr<Location> placement = std::make_shared<Location>(0, "Kuninkaanlinna");
    int connections = 5;
    std::shared_ptr<Agent> agent = std::make_shared<Agent>(name, placement, connections);
    QVERIFY2(agent->name() == name, "Virhe, name on väärin");
}

/**
 * @brief TestAgent::testTitle
 *
 * Testaa CardInterfacesta perityn title() funktion.
 *
 * Luodaan luokasta olio, jonka title pitäisi olla aina "".
 * Vamistetaan, että kortin title palauttaa oikean arvon.
 */
void TestAgent::testTitle() {
    QString name = QString("Agentti");
    std::shared_ptr<Location> placement = std::make_shared<Location>(0, "Kuninkaanlinna");
    int connections = 5;
    std::shared_ptr<Agent> agent = std::make_shared<Agent>(name, placement, connections);
    QVERIFY2(agent->title() == QString(""), "Virhe, title on väärin");
}

/**
 * @brief TestAgent::testLocation
 *
 * Testaa CardInterfacesta perityn location() funktion.
 *
 * 1) Luodaan luokasta olio ja annetaan sille placement (location) rakentajassa.
 * 1) Varmistetaan, että kortin location palauttaa oikean arvon.
 * 2) Luodaan luokasta olio ja annetaan sille tyhjä placement (location) rakentajassa.
 * 2) Varmistetaan, että kortin location palauttaa tyhjän osoittimen.
 */
void TestAgent::testLocation() {
    QString name = QString("Agentti");
    std::shared_ptr<Location> location = std::make_shared<Location>(0, "Kuninkaanlinna");
    int connections = 5;
    std::shared_ptr<Agent> agent = std::make_shared<Agent>(name, location, connections);
    QVERIFY2(agent->location().lock() == location, "Virhe, location on väärin");

    QString name2 = QString("Agentti2");
    std::weak_ptr<Location> location2 = std::weak_ptr<Location>();
    int connections2 = 0;
    std::shared_ptr<Agent> agent2 = std::make_shared<Agent>(name2, location2, connections2);
    QVERIFY2(agent2->location().expired(), "Virhe, location ei ole tyhjä");
}

/**
 * @brief TestAgent::testOwner
 *
 * Testaa CardInterfacesta perityn owner() funktion.
 *
 * 1) Luodaan luokasta olio ja asetetaan sille omistaja setOwner funktiolla.
 * 1) Varmistetaan, että kortin owner palauttaa oikean arvon.
 * 2) Luodaan luokasta olio ja ei aseteta sille ollenkaan omistajaa.
 * 2) Vamistetaan, että kortin owner palauttaa tyhjän osoittimen.
 */
void TestAgent::testOwner() {
    QString name = QString("Agentti");
    std::shared_ptr<Location> placement = std::make_shared<Location>(0, "Kuninkaanlinna");
    int connections = 5;
    std::shared_ptr<Agent> agent = std::make_shared<Agent>(name, placement, connections);
    std::weak_ptr<Game> game = std::weak_ptr<Game>();
    int playerId = 1;
    QString playerName = QString("Pelaaja 1");
    std::shared_ptr<Player> player = std::make_shared<Player>(game, playerId, playerName);
    agent->setOwner(player);
    QVERIFY2(agent->owner().lock()->name() == playerName, "Virhe, owner on väärin");

    QString name2 = QString("Agentti2");
    std::shared_ptr<Location> placement2 = std::make_shared<Location>(0, "Kuninkaanlinna");
    int connections2 = 5;
    std::shared_ptr<Agent> agent2 = std::make_shared<Agent>(name2, placement2, connections2);
    QVERIFY2(agent2->owner().expired(), "Virhe, owner ei ole tyhjä");
}

/**
 * @brief TestAgent::testSetOwner
 *
 * Testaa CardInterfacesta perityn setOwner(weak_ptr<Player> owner) funktion.
 *
 * 1) Luodaan luokasta olio ja asetetaan sille omistaja setOwner funktiolla.
 * 1) Varmistetaan, että kortin owner palauttaa oikean arvon.
 * 2) Luodaan luokasta olio ja asetetaan sille tyhjä omistaja setOwner funktiolla.
 * 2) Varmistetaan, että kortin owner palauttaa tyhjän osoittimen.
 */
void TestAgent::testSetOwner() {
    QString name = QString("Agentti");
    std::shared_ptr<Location> placement = std::make_shared<Location>(0, "Kuninkaanlinna");
    int connections = 5;
    std::shared_ptr<Agent> agent = std::make_shared<Agent>(name, placement, connections);
    std::weak_ptr<Game> game = std::weak_ptr<Game>();
    int playerId = 1;
    QString playerName = QString("Pelaaja 1");
    std::shared_ptr<Player> player = std::make_shared<Player>(game, playerId, playerName);
    agent->setOwner(player);
    QVERIFY2(agent->owner().lock()->name() == playerName, "Virhe, owner on väärin");

    QString name2 = QString("Agentti");
    std::shared_ptr<Location> placement2 = std::make_shared<Location>(0, "Kuninkaanlinna");
    int connections2 = 5;
    std::shared_ptr<Agent> agent2 = std::make_shared<Agent>(name2, placement2, connections2);
    std::weak_ptr<Player> player2 = std::weak_ptr<Player>();
    agent2->setOwner(player2);
    QVERIFY2(agent2->owner().expired(), "Virhe, owner ei ole tyhjä");
}

/**
 * @brief TestAgent::testIsCommon
 *
 * Testaa AgentInterfacesta perityn isCommon() funktion.
 *
 * 1) Luodaan luokasta olio ja annetaan sille tyhjä placement rakentajassa.
 * 1) Varmistetaan, että kortin isCommon palauttaa arvon true.
 * 2) Luodaan luokasta olio ja annetaan sille placement rakentajassa.
 * 2) Varmistetaan, että kortin isCommon palauttaa arvon false.
 */
void TestAgent::testIsCommon() {
    QString name = QString("Agentti");
    std::weak_ptr<Location> placement = std::weak_ptr<Location>();
    int connections = 0;
    std::shared_ptr<Agent> agent = std::make_shared<Agent>(name, placement, connections);
    QVERIFY2(agent->isCommon(), "Virhe, kortti ei ole geneerinen");

    QString name2 = QString("Agentti2");
    std::shared_ptr<Location> placement2 = std::make_shared<Location>(0, "Kuninkaanlinna");
    int connections2 = 5;
    std::shared_ptr<Agent> agent2 = std::make_shared<Agent>(name2, placement2, connections2);
    QVERIFY2(!agent2->isCommon(), "Virhe, kortti ei ole geneeritön");
}

/**
 * @brief TestAgent::testPlacement
 *
 * Testaa AgentInterfacesta perityn placement() funktion.
 *
 * 1) Luodaan luokasta olio ja annetaan sille placement rakentajassa.
 * 1) Varmistetaan, että kortin placement palauttaa oikean arvon.
 * 2) Luodaan luokasta olio ja annetaan tyhjä placement rakentajassa.
 * 2) Varmistetaa, että kortin placement palauttaa tyhjän osoittimen.
 */
void TestAgent::testPlacement() {
    QString name = QString("Agentti");
    std::shared_ptr<Location> placement = std::make_shared<Location>(0, "Kuninkaanlinna");
    int connections = 5;
    std::shared_ptr<Agent> agent = std::make_shared<Agent>(name, placement, connections);
    QVERIFY2(agent->placement().lock() == placement, "Virhe, placement on väärin");

    QString name2 = QString("Agentti2");
    std::weak_ptr<Location> placement2 = std::weak_ptr<Location>();
    int connections2 = 0;
    std::shared_ptr<Agent> agent2 = std::make_shared<Agent>(name2, placement2, connections2);
    QVERIFY2(agent2->placement().expired(), "Virhe, placement ei ole tyhjä");
}

/**
 * @brief TestAgent::testSetPlacement
 *
 * Testaa AgentInterfacesta perityn setPlacement(weak_ptr<Location> placement) funktion.
 *
 * 1) Luodaan luokasta olio ja asetetaan sille placement setPlacement funktiolla.
 * 1) Varmistetaan, että kortin placement palauttaa oikean arvon.
 * 2) Luodaan luokasta olio ja asetetaan sille tyhjä placement setPlacement funktiolla.
 * 2) Varmistetaan, että koritn placement palauttaa tyhjän osoittimen.
 */
void TestAgent::testSetPlacement() {
    QString name = QString("Agentti");
    std::shared_ptr<Location> placement = std::make_shared<Location>(0, "Kuninkaanlinna");
    int connections = 5;
    std::shared_ptr<Agent> agent = std::make_shared<Agent>(name, placement, connections);
    QVERIFY2(agent->placement().lock() == placement, "Virhe, placement on väärin");

    QString name2 = QString("Agentti2");
    std::shared_ptr<Location> placement2 = std::make_shared<Location>(0, "Kuninkaanlinna");
    int connections2 = 5;
    std::shared_ptr<Agent> agent2 = std::make_shared<Agent>(name2, placement2, connections2);
    agent2->setPlacement(std::weak_ptr<Location>());
    QVERIFY2(agent2->placement().expired(), "Virhe, placement ei ole tyhjä");
}

/**
 * @brief TestAgent::testConnections
 *
 * Testaa AgentInterfacesta perityn testConnections() funktion.
 *
 * 1) Luodaan luokasta olio ja asetetaan sille 0 suhdetta.
 * 1) Varmistetaan, että kortin connections palauttaa arvon 0.
 * 2) Luodaan luokasta olio ja asetetaan sille suhteita connections funktiolla.
 * 2) Varmistetaan, että kortin connections palauttaa oikean arvon.
 */
void TestAgent::testConnections() {
    QString name = QString("Agentti");
    std::shared_ptr<Location> placement = std::make_shared<Location>(0, "Kuninkaanlinna");
    int connections = 0;
    std::shared_ptr<Agent> agent = std::make_shared<Agent>(name, placement, connections);
    QVERIFY2(agent->connections() == 0, "Virhe, connections on väärin");

    QString name2 = QString("Agentti2");
    std::shared_ptr<Location> placement2 = std::make_shared<Location>(0, "Kuninkaanlinna");
    int connections2 = 0;
    std::shared_ptr<Agent> agent2 = std::make_shared<Agent>(name2, placement2, connections2);
    agent2->setConnections(5);
    QVERIFY2(agent2->connections() == 5, "Virhe, connections on väärin");
}

/**
 * @brief TestAgent::testSetConnections
 *
 * Testaa AgentInterfacesta perityn testSetConnections(unsigned short connections) funktion.
 *
 * 1) Luodaan luokasta olio ja asetetaan sille suhteita setConnections funktiolla.
 * 1) Varmistetaan, että kortin connections palauttaa oikean arvon.
 * 2) Luodaan luokasta olio ja asetetaan setConnections funktiolla invariantin rikkova arvo.
 *    Invariantti menee rikki 1: asettamalla suhteita, vaikka kortilla ei ole placementtia.
 * 2) Varmistetaan, että oliolta heitetään poikkeus StateException.
 */
void TestAgent::testSetConnections() {
    QString name = QString("Agentti");
    std::shared_ptr<Location> placement = std::make_shared<Location>(0, "Kuninkaanlinna");
    int connections = 0;
    std::shared_ptr<Agent> agent = std::make_shared<Agent>(name, placement, connections);
    agent->setConnections(5);
    QVERIFY2(agent->connections() == 5, "Virhe, connections on väärin");

    QString name2 = QString("Agentti2");
    std::weak_ptr<Location> placement2 = std::weak_ptr<Location>();
    int connections2 = 0;
    std::shared_ptr<Agent> agent2 = std::make_shared<Agent>(name2, placement2, connections2);
    QVERIFY_EXCEPTION_THROWN(agent2->setConnections(5), StateException);
}

/**
 * @brief TestAgent::testModifyConnections
 *
 * Testaa AgentInterfacesta perityn testModifyConnections(short change) funktion.
 *
 * 1) Luodaan luokasta olio ja asetetaan sille suhteita modifyConnections funktiolla.
 * 1) Varmistetaan, että kortin connections palauttaa oikean arvon.
 * 2) Luodaan luokasta olio ja asetetaan modifyConnections funktiolla invariantin rikkova arvo.
 *    Invariantti menee rikki 1: asettamalla suhteita, vaikka kortilla ei ole placementtia.
 *    Invariantti menee rikki 2: asettamalla negatiivisia suhteiden määriä.
 * 2) Varmistetaan, että oliolta heitetään poikkeus StateException.
 */
void TestAgent::testModifyConnections() {
    QString name = QString("Agentti");
    std::weak_ptr<Location> placement = std::weak_ptr<Location>();
    int connections = 0;
    std::shared_ptr<Agent> agent = std::make_shared<Agent>(name, placement, connections);
    QVERIFY_EXCEPTION_THROWN(agent->modifyConnections(5), StateException);

    QString name2 = QString("Agentti2");
    std::shared_ptr<Location> placement2 = std::make_shared<Location>(0, "Kuninkaanlinna");
    int connections2 = 0;
    std::shared_ptr<Agent> agent2 = std::make_shared<Agent>(name2, placement2, connections2);
    QVERIFY_EXCEPTION_THROWN(agent2->modifyConnections(-1), StateException);
}

QTEST_APPLESS_MAIN(TestAgent)

#include "tst_testagent.moc"
